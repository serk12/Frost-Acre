#include "../header/SimulatorManager.h"

SimulatorManager::SimulatorManager() : InstrumentSimulator() {}

Sound SimulatorManager::simulateAll(Instrument& instrument) {
    Sound sound = this->simulateString(instrument);
    // sound this->simulatePickup(sound);
    // sound this->simulateResonance(sound);
    return sound;
}
Sound SimulatorManager::simulateString(Instrument& instrument) {
    this->setInstrument(instrument);
    this->calculatePrecal();

    Sound *sound = new Sound();
    return *sound;
}
