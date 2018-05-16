#ifndef MIDIMANAGER_HH
#define MIDIMANAGER_HH

#include <Eigen/Dense>
#include <vector>
#include <map>

#include "../../../lib/midifile/include/MidiFile.h"
#include "../../Controller/header/DebugController.h"
#include "JsonManager.h"
#include "MidiUtils.h"

class MidiManager {
public:
    static std::vector<Pluck> parseMidiFile(std::string midiPath, std::string jsonFile);
    static std::map<std::string, Eigen::VectorXd> buildMapForces(std::string midiPath);
private:
    static std::map<std::string, Eigen::VectorXd> getMapForces(std::string jsonFIle);
};

#endif // ifndef MIDIMANAGER_HH
