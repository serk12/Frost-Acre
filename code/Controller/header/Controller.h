#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <vector>

#include "../../IOBundle/header/ObjManager.h"
#include "../../IOBundle/header/JsonManager.h"
#include "../../IOBundle/header/MidiManager.h"

#include "../../SimulatorBundle/header/SimulatorManager.h"
#include "../../SimulatorBundle/header/Instrument.h"

#include "DebugController.h"

#include "../../../lib/rapidjson/document.h"

class Controller {
public:
    Controller();
    Controller(std::string objFile, std::string jsonFile,
               std::string midiFile, std::string midiJsonFile);

    void setObjFile(std::string objFile);
    void setjsonFile(std::string jsonFile);
    void run();
private:
    void parseMaterial();

    std::vector<Material> material;
    std::string objFile;
    std::string jsonFile;
    std::string midiFile;
    std::string midiJsonFile;
};

#endif // ifndef CONTROLLER_HH
