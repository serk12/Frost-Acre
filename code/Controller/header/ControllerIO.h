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
    ControllerIO();
    ControllerIO(std::string objFile, std::string midiFile,
                 std::string midiJsonFile);
    ControllerIO(std::string objFile, std::string jsonFile,
                 std::string midiFile, std::string midiJsonFile,
                 std::string wavFile);

    Model3D readObj();
    void readJson(Pickup& pickup, std::vector<Material>& materials);
    std::vector<Pluck> parseMidiFile();
    std::map<int, Eigen::VectorXd> getMapForces();

    void writeJsonMidi(bool def = true);
    void writeWav(std::vector<double> sound, int sampleRate);

private:
    std::string objFile;
    std::string jsonFile;
    std::string midiFile;
    std::string midiJsonFile;
    std::string wavFile;
};

#endif // ifndef CONTROLLERIO_HH
