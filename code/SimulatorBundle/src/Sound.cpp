#include "../header/Sound.h"

Sound::Sound() {}

Sound::Sound(std::vector<Frequency>frequency) : Sound() {
    this->frequency = frequency;
}

void Sound::setFrequencys(std::vector<Frequency>frequency) {
    this->frequency = frequency;
}

std::vector<Frequency>Sound::getFrequencysByRange() {}

std::vector<Frequency>Sound::getFrequencysByPosition() {}
