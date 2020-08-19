#include <vector>

#include "Voice.h"

constexpr int VOICE_NUM = 32;

class VoiceManager {
    std::vector<Voice> voice;
public:
    VoiceManager();

    void noteOn(int channel, int noteNo, float velocity);

    void noteOff(int noteNo);

    void update();

    float process();
    
    void setADSR(float a, float d, float s, float r);
};
