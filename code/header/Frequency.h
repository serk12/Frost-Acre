#ifndef FREQUENCY_HH
#define FREQUENCY_HH

class Frequency {
public:
    Frequency();
    Frequency(float possString);
    Frequency(float freq, float possString);
    Frequency(float freq, float possString, float amplitude);

    float getFreq();
    void  setFreq(float freq);

    float getPossString();
    void  setPossString(float poss);

    float getAmplitude();
    void  setAmplitude(float amplitude);

private:
    // la posicion 0 sera siguiendo el clavijero del instrumento
    float possString;
    float freq;
    float amplitude;
};

#endif // ifndef FREQUENCY_HH
