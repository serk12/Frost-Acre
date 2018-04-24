#ifndef SOUND_HH
#define SOUND_HH

#include <vector>

#include "Frequency.h"

class Sound {
public:
    Sound();
    Sound(std::vector<Frequency>frequency);

    void setFrequencys(std::vector<Frequency>frequency);

    std::vector<Frequency>getFrequencysByRange();
    std::vector<Frequency>getFrequencysByPosition();

private:
    std::vector<Frequency>frequency;
};

#endif // ifndef SOUND_HH
