#include "Oscillator.h"

class Voice {
    int key;
    Oscillator osc;
public:
    void start(int channel, int noteNo, float velocity);

    void stop();

    void update();

    float process();

    int getState() { return osc.getState(); };

    int getKey() { return key; };
};