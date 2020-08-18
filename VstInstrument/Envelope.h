constexpr int ENV_STOP = 0;
constexpr int ENV_ATTACK = 1;
constexpr int ENV_DECAY = 2;
constexpr int ENV_SUSTAIN = 3;
constexpr int ENV_RELEASE = 4;

class Envelope {
    float volume;
    float volumeReleased;

    int state;

    float attack;
    float decay;
    float sustain;
    float release;

public:
    Envelope();

    void start();

    void stop();

    void update();

    float process();

    void setADSR(float a, float d, float s, float r);

    int getState() { return state; }
};