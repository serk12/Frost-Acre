#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <vector>
#include <list>
#include <sstream>

#include "../../IOBundle/header/ObjManager.h"
#include "../../IOBundle/header/WavManager.h"
#include "../../IOBundle/header/JsonManager.h"
#include "../../IOBundle/header/MidiManager.h"

#include "../../SimulatorBundle/header/Instrument.h"
#include "../../SimulatorBundle/header/SimulatorManager.h"

#include "DebugController.h"

#include "../../../lib/rapidjson/document.h"

class Controller {
public:
    Controller();
    Controller(std::string objFile, std::string jsonFile,
               std::string midiFile, std::string midiJsonFile,
               std::string wavFile);

    Controller(std::string midiFile, std::string midiJsonFile);

    void run();
    void writeJsonMidi(bool def = true);
private:
    void readJson();
    void readJsonMidi();

    std::vector<Material> material;
    std::string objFile;
    std::string jsonFile;
    std::string midiFile;
    std::string midiJsonFile;
    std::string wavFile;
};

#endif // ifndef CONTROLLER_HH
