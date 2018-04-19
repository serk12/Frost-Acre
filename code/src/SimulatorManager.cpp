#include "../header/SimulatorManager.h"

SimulatorManager::SimulatorManager() : StringSimulator() {}

Sound SimulatorManager::simulateAll(String string) {
    Sound sound = this->simulateString(string);
    // sound this->simulatePickup(sound);
    // sound this->simulateResonance(sound);
    return sound;
}
Sound SimulatorManager::simulateString(String string) {
    this->setString(string);
    this->calculatePrecal();
}
