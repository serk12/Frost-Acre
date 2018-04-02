#ifndef NOTE_HH
#define NOTE_HH

#include <vector>

#include "Frequency.h"

class Note {
public:

    Note();
    Note(std::vector<Frequency>frequency);

    void setFrequencys(std::vector<Frequency>frequency);

    std::vector<Frequency>getFrequencysByRange();
    std::vector<Frequency>getFrequencysByPosition();

private:

    std::vector<Frequency>frequency;
};

#endif // ifndef NOTE_HH
