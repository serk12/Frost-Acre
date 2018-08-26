#ifndef CONTROLLERIO_HH
#define CONTROLLERIO_HH

#include <sstream>

#include "../../IOBundle/header/ObjManager.h"
#include "../../IOBundle/header/WavManager.h"
#include "../../IOBundle/header/JsonManager.h"
#include "../../IOBundle/header/MidiManager.h"

#include "../../../lib/rapidjson/document.h"

#include "DebugController.h"

class ControllerIO {
public:
    static const int initMidi;
    static const int endMidi;

    ControllerIO();
    ControllerIO(std::string objFile, std::string midiJsonFile);
    ControllerIO(std::string objFile, std::string jsonFile, std::string prerenderFile);
    ControllerIO(std::string prerenderFile, std::string midiFile,
                 std::string midiJsonFile, std::string wavFile);

    Model3D readObj();

    void readJson(Pickup& pickup, std::vector<Material>& materials, Resonance& resonance);

    std::vector<Pluck> readMidiFile();

    void writeJsonMidi();
    std::map<int, Eigen::VectorXd> readJsonMidi();

    void writePrerender(Instrument& instrument);
    Instrument readPrerender();

    void writeWav(std::vector<double> sound, int sampleRate);

private:
    void readJson(Pickup& pickup, std::vector<Material>& materials, Resonance& resonance, rapidjson::Document& doc);
    std::string objFile;
    std::string jsonFile;
    std::string midiFile;
    std::string midiJsonFile;
    std::string prerenderFile;
    std::string wavFile;
};

#endif // ifndef CONTROLLERIO_HH
