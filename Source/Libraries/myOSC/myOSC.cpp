// The Audio Programming Book - Boulanger, Lazzarini, Mathews

#include "myOSC.h"
#include "math.h"

myOsc::myOsc() {
    // Set the phase to zero when the Oscillator is instantiated
    phase = 0.0;
}

double myOsc::sine(double frequency) {        
    output = (float)sin(phase);
    phase += frequency * M_TWOPI / sampleRate;
    
    if (phase >= M_TWOPI)
        phase -= M_TWOPI;

    return output;
}

double myOsc::square(double frequency) {
    if (phase <= M_PI)
        output = 1.;
    else
        output = -1.;

    phase += frequency * M_TWOPI / sampleRate;

    if (phase >= M_TWOPI)
        phase -= M_TWOPI;

    return output;
}

double myOsc::saw(double frequency) {
    output = 1. - (phase / M_PI);
    phase += frequency * M_TWOPI / sampleRate;

    if (phase >= M_TWOPI)
        phase -= M_TWOPI;

    return output;
}

double myOsc::triangle(double frequency) {
    output = (phase / M_PI) - 1.;
    if (output < 0)
        output = -output;

    phase += frequency * M_TWOPI / sampleRate;

    if (phase >= M_TWOPI)
        phase -= M_TWOPI;

    return output;
}

double myOsc::noise() {

    constexpr double epsilon = std::numeric_limits<double>::epsilon();

    //initialize the random uniform number generator (runif) in a range 0 to 1
    static std::mt19937 rng(std::random_device{}()); // Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> runif(0.0, 1.0);

    //create two random numbers, make sure u1 is greater than epsilon
    double u1, u2;
    do
    {
        u1 = runif(rng);
    } while (u1 <= epsilon);
    u2 = runif(rng);

    auto mag = 0.25 * sqrt(-2.0 * log(u1));
    auto output = mag * cos(M_TWOPI * u2);

    return output;
}





