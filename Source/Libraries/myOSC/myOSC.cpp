// The Audio Programming Book - Boulanger, Lazzarini, Mathews

#include "myOSC.h"
#include "math.h"

myOsc::myOsc() {
    // Set the phase to zero when the Oscillator is instantiated
    phase = 0.0;
}

double myOsc::sine(double frequency) {        
    output = (float)sin(phase);
    phase += frequency * TWOPI / sampleRate;
    
    if (phase >= TWOPI)
        phase -= TWOPI;

    return output;
}

double myOsc::square(double frequency) {
    if (phase <= PI)
        output = 1.;
    else
        output = -1.;

    phase += frequency * TWOPI / sampleRate;

    if (phase >= TWOPI)
        phase -= TWOPI;

    return output;
}

double myOsc::saw(double frequency) {
    output = 1. - (phase / PI);
    phase += frequency * TWOPI / sampleRate;

    if (phase >= TWOPI)
        phase -= TWOPI;

    return output;
}

double myOsc::triangle(double frequency) {
    output = (phase / PI) - 1.;
    if (output < 0)
        output = -output;

    phase += frequency * TWOPI / sampleRate;

    if (phase >= TWOPI)
        phase -= TWOPI;

    return output;
}

double myOsc::noise() {
    //u1 = rand() / (float)RAND_MAX;
    //u2 = rand() / (float)RAND_MAX;

    //phi = TWOPI * u1;
    //r = sqrt(-2. * log(1. - u2));

    //output = r * (float)cos(phi);
    r = rand() / (float)RAND_MAX;
    output = r * 2. - 1.;
    return output;
}


