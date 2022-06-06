/*
  ==============================================================================

    myAudioLibrary.cpp
    Created: 31 May 2022 4:24:01pm
    Author:  User

  ==============================================================================
*/

#include "myAudioLibrary.h"

// =============== OVERDRIVE ===================
double myODfx::overdrive(double input, float gain, float wet) {
    // juce returns float, I need double.
    wet = double(wet);
    gain = double(gain);
    output = gain * input;

    xM = abs(output);

    if (xM <= 0.3333)
        output *= 2;
    else if (xM > 0.3333 || xM <= 0.6666)
        if (input < 0)
            output = (-3. + (2. - 3. * xM) * (2. - 3. * xM)) / 3.;
        else
            output = (3. - (2. - 3. * xM) * (2. - 3. * xM)) / 3.;
    else
        if (input < 0)
            output = -1.;
        else
            output = 1.;

    return (1. - wet) * input + wet * output;
}

double myODfx::distortion(double input, float gain, float wet) {
    wet = double(wet);
    gain = double(gain);
    output = 1.5 * input;

    xM = abs(output);

    if (input < 0)
        output = -1. + exp(-gain * xM);
    else
        output = 1. - exp(-gain * xM);

    return (1. - wet) * input + wet * output;
}

// =============== ENVELOPE ===================
double myEnvelope::adsr(double input, int trigger) {
    /* We can think the ADSR envelope as a system composed by 4 states: attack, decay, sustain and release.
    We want to implement the transition between the different stages. */
    if (trigger == 1 && aphase != 1 && sphase != 1 && dphase != 1) {
        dphase = 0;
        sphase = 0;
        rphase = 0;
        aphase = 1;
    }

    // Attack Phase
    if (aphase == 1) {
        rphase = 0;
        curramp += attack;
        output = input * curramp;

        if (curramp >= 0.99999) {
            curramp = 1.;
            aphase = 0;
            dphase = 1;
        }
    }

    // Decay Phase
    if (dphase == 1) {
        curramp *= decay;
        output = input * curramp;
        if (curramp <= sustain + 0.00001) {
            curramp = sustain;
            dphase = 0;
            sphase = 1;
        }
    }

    // Sustain Phase
    if (sphase == 1) {
        output = input * curramp;

        if (trigger != 1) {
            sphase = 0;
            rphase = 1;
        }
    }

    // Release Phase
    if (rphase == 1 && curramp > 0.) {
        curramp *= release;
        output = input * curramp;

    }

    return output;
}

void myEnvelope::setAttack(double attack_ms) {
    attack = 1 - exp(-1.0 / (attack_ms * sampleRate * 0.001));
}

void myEnvelope::setDecay(double decay_ms) {
    decay = exp(-1.0 / (decay_ms * sampleRate * 0.001));
}

void myEnvelope::setSustain(double sustain_level) {
    sustain = sustain_level;
}

void myEnvelope::setRelease(double release_ms) {
    release = exp(-1.0 / (release_ms * sampleRate * 0.001));
}



// =============== FILTERS ===================
double myFilter::LPF1ord(double input, float cutoff) {
    // forward delay line
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Coefficients
    b0 = k / (k + 1.);
    b1 = b0;
    a1 = (k - 1.) / (k + 1.);
    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] - a1 * outputs[1];
    // Update delay line
    outputs[1] = output;
    return output;
}

double myFilter::HPF1ord(double input, float cutoff) {
    // forward delay line
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Coefficients
    b0 = 1. / (k + 1.);
    b1 = -b0;
    a1 = (k - 1.) / (k + 1.);
    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] - a1 * outputs[1];
    // Update delay line
    outputs[1] = output;
    return output;
}

double myFilter::LPF2ord(double input, float cutoff, float Q) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Coefficients
    b0 = k * k * Q / (k * k * Q + Q + k);
    b1 = 2. * b0;
    b2 = b0;
    a1 = 2. * Q * (k * k - 1.) / (k * k * Q + k + Q);
    a2 = (k * k * Q - k + Q) / (k * k * Q + k + Q);
    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;
    return output;
}

double myFilter::HPF2ord(double input, float cutoff, float Q) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Coefficients
    b0 = Q / (k * k * Q + Q + k);
    b1 = -2. * Q / (k * k * Q + Q + k);
    b2 = b0;
    a1 = 2. * Q * (k * k - 1.) / (k * k * Q + k + Q);
    a2 = (k * k * Q - k + Q) / (k * k * Q + k + Q);
    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;
    return output;
}

double myFilter::BPF2ord(double input, float cutoff, float Q) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Coefficients
    b0 = k / (k * k * Q + Q + k);
    b2 = -b0;
    a1 = 2. * Q * (k * k - 1.) / (k * k * Q + k + Q);
    a2 = (k * k * Q - k + Q) / (k * k * Q + k + Q);
    // Finite difference equation
    output = b0 * inputs[0] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;
    return output;
}

double myFilter::LPShelving(double input, float cutoff, float gain_lin) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Useful variables
    double k2 = k * k;
    double V0k2 = gain_lin * k * k;
    double sqrt2V0 = sqrt(2. * gain_lin);
    // Coefficients
    if (gain_lin >= 1.) {
        b0 = (1. + sqrt2V0 * k + V0k2)  / (1. + M_SQRT2 * k + k2);
        b1 = (2. * (V0k2 - 1.))         / (1. + M_SQRT2 * k + k2);
        b2 = (1. - sqrt2V0 * k + V0k2)  / (1. + M_SQRT2 * k + k2);
        a1 = (2. * (k2 - 1.))           / (1. + M_SQRT2 * k + k2);
        a2 = (1. - M_SQRT2 * k + k2)    / (1. + M_SQRT2 * k + k2);
    }
    else {
        b0 = (gain_lin * (1. + M_SQRT2 * k + k2))   / (gain_lin + sqrt2V0 * k + k2);
        b1 = (2. * gain_lin * (k2 - 1.))            / (gain_lin + sqrt2V0 * k + k2);
        b2 = (gain_lin * (1. - M_SQRT2 * k + k2))   / (gain_lin + sqrt2V0 * k + k2);
        a1 = (2. * (k2 - gain_lin))                 / (gain_lin + sqrt2V0 * k + k2);
        a2 = (gain_lin - sqrt2V0 * k + k2)          / (gain_lin + sqrt2V0 * k + k2);
    }
  
    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;
    return output;
}

double myFilter::HPShelving(double input, float cutoff, float gain_lin) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Useful variables
    double k2 = k * k;
    double V0k2 = gain_lin * k * k;
    double sqrt2V0 = sqrt(2. * gain_lin);
    // Coefficients
    if (gain_lin >= 1.) {
        b0 = (gain_lin + sqrt2V0 * k + k2)  / (1. + M_SQRT2 * k + k2);
        b1 = (2. * (k2 - gain_lin))         / (1. + M_SQRT2 * k + k2);
        b2 = (gain_lin - sqrt2V0 * k + k2)  / (1. + M_SQRT2 * k + k2);
        a1 = (2. * (k2 - 1.))               / (1. + M_SQRT2 * k + k2);
        a2 = (1. - M_SQRT2 * k + k2)        / (1. + M_SQRT2 * k + k2);
    }
    else {
        b0 = (gain_lin * (1. + M_SQRT2 * k + k2))   / (1. + sqrt2V0 * k + V0k2);
        b1 = (2. * gain_lin * (k2 - 1.))            / (1. + sqrt2V0 * k + V0k2);
        b2 = (gain_lin * (1. - M_SQRT2 * k + k2))   / (1. + sqrt2V0 * k + V0k2);
        a1 = (2. * (V0k2 - 1.))                     / (1. + sqrt2V0 * k + V0k2);
        a2 = (1. - sqrt2V0 * k + V0k2)              / (1. + sqrt2V0 * k + V0k2);
    }

    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;
    return output;
}

double myFilter::Peak(double input, float cutoff, float Q, float gain_lin) {
    // forward delay line
    inputs[2] = inputs[1];
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    k = tan(M_PI * cutoff / sampleRate);
    // Useful variables
    double k2 = k * k;
    double V0_Q = gain_lin / Q;
    double invV0Q = 1. / (gain_lin * (double)Q);
    double invQ = 1. / Q;

    // Coefficients
    if (gain_lin >= 1.) {
        b0 = (1. + V0_Q * k + k2)  / (1. + invQ * k + k2);
        b1 = (2. * (k2 - 1.))         / (1. + invQ * k + k2);
        b2 = (1. - V0_Q * k + k2)  / (1. + invQ * k + k2);
        a1 = b1;
        a2 = (1. - invQ * k + k2)        / (1. + invQ * k + k2);
    }
    else {
        b0 = (1. + invQ * k + k2)   / (1. + invV0Q * k + k2);
        b1 = (2. * (k2 - 1.))       / (1. + invV0Q * k + k2);
        b2 = (1. - invQ * k + k2)   / (1. + invV0Q * k + k2);
        a1 = b1;
        a2 = (1. - invV0Q * k + k2) / (1. + invV0Q * k + k2);
    }

    // Finite difference equation
    output = b0 * inputs[0] + b1 * inputs[1] + b2 * inputs[2] - a1 * outputs[1] - a2 * outputs[2];
    // Update delay line
    outputs[2] = outputs[1];
    outputs[1] = output;

    return output;
}

// =============== OSCILLATORS ===================
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
    // Box-Muller transform, script from wikipedia
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