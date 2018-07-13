#include "../header/Controller.h"

Controller::Controller() {}

Controller::Controller(std::string objFile, std::string jsonFile,
                       std::string midiFile, std::string midiJsonFile,
                       std::string wavFile)
    : ControllerIO(objFile, jsonFile, midiFile, midiJsonFile, wavFile) {}

Controller::Controller(std::string objFile, std::string midiFile, std::string midiJsonFile)
    : ControllerIO(objFile, midiFile, midiJsonFile) {}

void Controller::run() {
    DebugController::startClock();

    DebugController::print("INIT RUN");
    DebugController::print("INIT PARSE");
    Pickup pickup;
    std::vector<Material> material;
    this->readJson(pickup, material);
    Model3D model = this->readObj();
    Instrument instrument(material, model);
    DebugController::print("END PARSE");

    DebugController::print("INIT PRECALC");
    SimulatorManager simMan = SimulatorManager();
    simMan.precallSimulator(instrument);
    simMan.setRadiusPickup(pickup.radiusPickup);
    simMan.setMagneticChargeDensity(pickup.magneticChargeDensity);
    simMan.setPickupPossition(pickup.pickupPossitionX, pickup.pickupPossitionY, pickup.pickupPossitionZ);
    DebugController::print("END PRECALC");

    DebugController::print("INIT FRAMES");
    std::vector<Pluck> plucks            = this->parseMidiFile();
    std::map<int, Eigen::VectorXd> notes = this->getMapForces();
    std::vector<double> sound            = runSimulator(plucks, notes, simMan);
    DebugController::print("END FRAMES");

    DebugController::print("WRITING WAV");
    this->writeWav(sound, (int)(SimulatorManager::SampleRate));
    DebugController::print("END SIMULATION");
    DebugController::print(instrument);
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
