#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include "Utils.h"
#include "StringSimulator.h"

class SimulatorManager : protected StringSimulator {
public:
    SimulatorManager();
    Sound simulateAll(String string);
    Sound simulateString(String string);
    // Sound simulatePickup(Sound sound);
    // Sound simulateResonance(Sound sound);

private:
};

#endif // ifndef SIMULATORMANAGER_HH
