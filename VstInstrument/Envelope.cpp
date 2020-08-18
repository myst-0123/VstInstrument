#include "Envelope.h"

Envelope::Envelope()
    : volume(0.0f),
      volumeReleased(0.0f),
      state(ENV_STOP)
{
    setADSR(50.0f, 300.0f, 0.5f, 1000.0f);
}

void Envelope::start()
{
    volume = 0.0f;
    volumeReleased = 0.0f;

    state = ENV_ATTACK;
}

void Envelope::stop()
{
    volumeReleased = volume;

    state = ENV_RELEASE;
}

void Envelope::update()
{
    switch(state) {
    case ENV_ATTACK:
        volume = volume + attack;

        if (volume >= 1.0f) {
            volume = 1.0f;
            state = ENV_DECAY;
        }

        return;
    case ENV_DECAY:
        volume = volume - (1.0f - sustain) * decay;

        if (volume <= sustain) {
            volume = sustain;
            state = ENV_SUSTAIN;
        }

        return;
    case ENV_SUSTAIN:
        return;
    case ENV_RELEASE:
        volume = volume - (volumeReleased) * release;

        if (volume <= 0) {
            volume = 0.0f;
            state = ENV_STOP;
        }
        
        return;
    case ENV_STOP:
        volume = 0.0f;
        
        return;
    default:
        volume = 0.0f;

        return;
    }
}

float Envelope::process()
{
    return volume;
}

void Envelope::setADSR(float a, float d, float s, float r)
{
    attack = 1.0f / (48000.0f * a / 1000.0f);
    decay = 1.0f / (48000.0f * d / 1000.0f);
    sustain = sustain;
    release = 1.0f / (48000.0f * r / 1000.0f);
}