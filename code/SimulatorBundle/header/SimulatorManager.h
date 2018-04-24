#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

// #include "../../UtilsDebug.h"
#include "StringSimulator.h"

class SimulatorManager : protected StringSimulator {
public:
    SimulatorManager();
    Sound simulateAll(String& string, Instrument& instrument);
    Sound simulateString(String& string, Instrument& instrument);
    // Sound simulatePickup(Sound sound);
    // Sound simulateResonance(Sound sound);

private:
};

#endif // ifndef SIMULATORMANAGER_HH
