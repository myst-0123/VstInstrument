class Oscillator {
    float pitch;
    float theta;
public:
    Oscillator();

    void start(float freq);

    void stop();

    void update();

    float process();
};
