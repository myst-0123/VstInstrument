#include "Oscillator.h"
#include "Envelope.h"

class Voice {
    int key;
    Oscillator osc;
    Envelope env;
public:
    void start(int channel, int noteNo, float velocity);

    void stop();

    void update();

    float process();

    int getState() { return env.getState(); };

    int getKey() { return key; };
};