constexpr int ENVGEN_ON = 0;
constexpr int ENVGEN_STOP = 1;

class Oscillator {
    float pitch;
    float theta;
    float env;
    int state;
public:
    Oscillator();

    void start(float freq);

    void stop();

    void update();

    float process();

    int getState() { return state; }
};
