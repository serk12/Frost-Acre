#include "../header/Note.h"

Note::Note() {}

Note::Note(std::vector<Frequency>frequency) : Note() {
    this->frequency = frequency;
}

void Note::setFrequencys(std::vector<Frequency>frequency) {
    this->frequency = frequency;
}

std::vector<Frequency>Note::getFrequencysByRange() {}

std::vector<Frequency>Note::getFrequencysByPosition() {}
