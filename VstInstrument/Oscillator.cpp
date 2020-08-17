#include "Oscillator.h"

#include <math.h>

Oscillator::Oscillator() : pitch(440.0f), 
                           theta(0.0f), 
                           env(0.0f), 
                           state(ENVGEN_STOP) 
{ }

void Oscillator::start(float freq)
{
    pitch = freq;
    theta = 0.0f;
    env = 1.0f;
    state = ENVGEN_ON;
}

void Oscillator::stop()
{
    env = 0.0f;
    state = ENVGEN_STOP;
}

void Oscillator::update()
{
    const float PI = 3.14159265f;
    theta += (2.0f * PI * pitch) / 48000.0f;
}

float Oscillator::process()
{
    return env * sin(theta);
}
