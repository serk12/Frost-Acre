#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <vector>

#include "../../InputBundle/header/ObjManager.h"
#include "../../InputBundle/header/JsonManager.h"

#include "../../SimulatorBundle/header/SimulatorManager.h"
#include "../../SimulatorBundle/header/Instrument.h"

#include "../../DebugUtils.h"

class Controller {
public:
    Controller();
    Controller(std::string objFile, std::string jsonFile);

    void setObjFile(std::string objFile);
    void setjsonFile(std::string jsonFile);
    void run();
private:
    void parseMaterial();

    std::vector<Material> materials;
    std::string objFile;
    std::string jsonFile;
};

#endif // ifndef CONTROLLER_HH
