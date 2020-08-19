#include "VoiceManager.h"

VoiceManager::VoiceManager() : voice(VOICE_NUM) { }

void VoiceManager::noteOn(int channel, int noteNo, float velocity)
{
    for (auto& i : voice) {
        if (i.getState() == ENV_STOP) {
            i.start(channel, noteNo, velocity);
            return;
        }
    }
}

void VoiceManager::noteOff(int noteNo)
{
    for (auto& i : voice) {
        if (i.getKey() == noteNo) {
            if (i.getState() == ENV_STOP) continue;
        }
        else {
            i.stop();
        }
    }
}

void VoiceManager::update()
{
    for (auto& i : voice)
        i.update();
}

float VoiceManager::process()
{
    float result = 0.0f;
    for (auto& i : voice)
        result += i.process();

    return result;
}

void VoiceManager::setADSR(float a, float d, float s, float r)
{
    for (auto& i : voice)
        i.setADSR(a, d, s, r);
}
