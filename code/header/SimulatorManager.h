#ifndef SIMULATORMANAGER_HH
#define SIMULATORMANAGER_HH

#include "Utils.h"
#include "InstrumentSimulator.h"

class SimulatorManager : protected InstrumentSimulator {
public:
    Sound simulateAll(String string);
    Sound simulateString(String string);
    // Sound simulatePickup(Sound sound);
    // Sound simulateResonance(Sound sound);

private:
};

#endif // ifndef SIMULATORMANAGER_HH
