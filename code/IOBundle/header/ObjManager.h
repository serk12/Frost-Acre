#ifndef OBJMANAGER_HH
#define OBJMANAGER_HH

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "../../Controller/header/DebugController.h"
#include "../../SimulatorBundle/header/EigenUtils.h"

class ObjManager {
public:
    static Model3D readObj(std::string filepath);

private:
    static std::vector<std::string> splitString(const std::string& s, const char token);
};

#endif // ifndef OBJMANAGER_HH
