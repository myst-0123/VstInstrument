#include "Oscillator.h"

class Voice {
    int noteNo;
    Oscillator osc;
public:
    Voice();

    void start(int channel, int noteNo, float velocity);

    void stop();

    void update();

    float process();
};