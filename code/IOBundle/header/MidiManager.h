#ifndef MIDIMANAGER_HH
#define MIDIMANAGER_HH

#include <Eigen/Dense>
#include <vector>
#include <map>


#include "../../../lib/midifile/include/MidiFile.h"
#include "JsonManager.h"


struct Pluck {
    Eigen::VectorXd force;
    float           timeForce;
    float           timeDur;
    float           timeStart;
};

class MidiManager {
public:
    static std::vector<Pluck> parseMidiFile(std::string midiPath, std::string jsonFile);
private:
    static std::map<std::string, Eigen::VectorXd> getMapForces(std::string jsonFIle);
};

#endif // ifndef MIDIMANAGER_HH
