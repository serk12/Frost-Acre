#include "../header/Controller.h"

Controller::Controller() {}

Controller::Controller(std::string prerenderFile,
                       std::string midiFile, std::string midiJsonFile,
                       std::string wavFile)
    : ControllerIO(prerenderFile, midiFile, midiJsonFile, wavFile) {}

Controller::Controller(std::string objFile, std::string infoFile, std::string writeFile)
    : ControllerIO(objFile, infoFile, writeFile) {}

void Controller::calcPrerender() {
    Pickup pickup;
    std::vector<Material> material;
    Resonance resonance;
    this->readJson(pickup, material, resonance);
    Model3D model = this->readObj();
    Instrument instrument(material, model, resonance, pickup);

    DebugController::print("INIT PRECALC");
    SimulatorManager simMan = SimulatorManager();
    simMan.precallSimulator(instrument);
    DebugController::print("END PRECALC");

    this->writePrerender(instrument);
}

void Controller::run() {
    DebugController::startClock();

    DebugController::print("INIT RUN");

    DebugController::print("INIT PARSE");
    Instrument instrument; instrument = this->readPrerender();
    SimulatorManager simMan           = SimulatorManager();
    simMan.setPrerender(instrument);
    DebugController::print("END PARSE");

    // double mag = 0; std::string ok;
    // while (std::cin >> ok) {
    // simMan.setMagneticChargeDensity(mag);
    // std::cout << "mag: " << mag << std::endl;

    DebugController::print("INIT FRAMES");
    std::vector<Pluck> plucks            = this->readMidiFile();
    std::map<int, Eigen::VectorXd> notes = this->readJsonMidi();
    std::vector<double> sound            = runSimulator(plucks, notes, simMan);
    DebugController::print("END FRAMES");

    DebugController::print("INIT WRITING WAV");
    this->writeWav(sound, (int)(SimulatorManager::SampleRate));
    DebugController::print("INIT WRITING WAV");

    DebugController::print("END SIMULATION");
    DebugController::print(instrument);
    // mag += 1;
    // }
}


std::vector<double> Controller::runSimulator(const std::vector<Pluck>& plucks,
                                             const std::map<int, Eigen::VectorXd>& notes,
                                             SimulatorManager& simMan) {
    float max = 0;
    for (auto& pluck : plucks) {
        float endNote = pluck.timeDur + pluck.timeStart;
        if (endNote > max) max = endNote;
    }
    std::vector<double> sound(ceil(max * SimulatorManager::SampleRate), 0);

    for (unsigned int i = 0; i < plucks.size(); ++i) {
        auto& pluck = plucks[i];
        std::vector<double> waves;

        simMan.calculateFrame(notes.at(pluck.note), pluck.timeForce, pluck.timeDur, waves);
        const int j = ceil(pluck.timeStart * SimulatorManager::SampleRate);

        #pragma omp parallel shared(sound, waves)
        {
            #pragma omp for
            for (unsigned int i = 0; i < waves.size(); ++i) {
                int x = j + i;
                #pragma omp atomic
                sound[x] += waves[i];
            }
        }
    }
    return sound;
}
