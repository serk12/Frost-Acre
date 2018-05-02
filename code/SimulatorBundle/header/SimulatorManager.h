#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include <Eigen/Eigenvalues>

// #include "../../Controller/header/DebugController.h"
#include "InstrumentSimulator.h"

class SimulatorManager : protected InstrumentSimulator {
public:
    SimulatorManager();
    Sound simulateAll(Instrument& instrument);
    Sound simulateString(Instrument& instrument);
    // Sound simulatePickup(Sound sound);
    // Sound simulateResonance(Sound sound);

private:
};

#endif // ifndef SIMULATORMANAGER_HH
