#include "../header/Frequency.h"

Frequency::Frequency() {}

Frequency::Frequency(float possString) : Frequency() {
    this->possString = possString;
}

Frequency::Frequency(float freq, float possString) : Frequency(possString) {
    this->freq = freq;
}

Frequency::Frequency(float freq, float possString, float amplitude)
    : Frequency(freq, possString) {
    this->amplitude = amplitude;
}

float Frequency::getFreq() {
    return freq;
}

void Frequency::setFreq(float freq) {
    this->freq = freq;
}

float Frequency::getPossString() {
    return possString;
}

void Frequency::setPossString(float poss) {
    this->possString = poss;
}

float Frequency::getAmplitude() {
    return amplitude;
}

void Frequency::setAmplitude(float amplitude) {
    this->amplitude = amplitude;
}
