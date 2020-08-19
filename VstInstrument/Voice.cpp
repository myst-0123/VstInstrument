#include "Voice.h"

#include <math.h>

void Voice::start(int channel, int noteNo, float velocity)
{
    key = noteNo;
    float pitch = (float)(440.0 * powf(2.0, (double)(key - (69)) / 12.0));

    osc.start(pitch);
    env.start();
}

void Voice::stop()
{
    osc.stop();
    env.stop();
}

void Voice::update()
{
    osc.update();
    env.update();
}

float Voice::process()
{
    float out = 0.0f;

    out = osc.process();
    out = out * env.process();

    return out;
}