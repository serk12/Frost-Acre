#include "../header/SimulatorManager.h"

SimulatorManager::SimulatorManager() : StringSimulator() {}

Sound SimulatorManager::simulateAll(String& string, Instrument& instrument) {
    Sound sound = this->simulateString(string, instrument);
    // sound this->simulatePickup(sound);
    // sound this->simulateResonance(sound);
    return sound;
}
Sound SimulatorManager::simulateString(String& string, Instrument& instrument) {
    this->setString(string);
    this->setInstrument(instrument);
    this->calculatePrecal();

    Sound *sound = new Sound();
    return *sound;
}
