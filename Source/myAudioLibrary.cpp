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

    output /= gain;

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
    attack = 1 - pow(0.01, 1.0 / (attack_ms * sampleRate * 0.001));
}

void myEnvelope::setDecay(double decay_ms) {
    decay = pow(0.01, 1.0 / (decay_ms * sampleRate * 0.001));
}

void myEnvelope::setSustain(double sustain_level) {
    sustain = sustain_level;
}

void myEnvelope::setRelease(double release_ms) {
    release = pow(0.01, 1.0 / (release_ms * sampleRate * 0.001));
}


// =============== FILTERS ===================
double myFilter::LPF1ord(double input, float cutoff) {
    // forward delay line
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    theta = M_TWOPI * cutoff / sampleRate;
    gamma = cos(theta) / (1.f + sin(theta));
    // Coefficients
    a0 = (1.f - gamma) / 2;
    a1 = a0;
    b1 = -gamma;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] - b1 * outputs[1];
    // Update delay line
    outputs[1] = output;
    return output;
}

double myFilter::HPF1ord(double input, float cutoff) {
    // forward delay line
    inputs[1] = inputs[0];
    inputs[0] = input;
    // Parameters
    theta = M_TWOPI * cutoff / sampleRate;
    gamma = cos(theta) / (1.f + sin(theta));
    // Coefficients
    a0 = (1.f + gamma) / 2;
    a1 = -(1.f - gamma) / 2;
    b1 = -gamma;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] - b1 * outputs[1];
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
    theta = M_TWOPI * cutoff / sampleRate;
    d = 1 / Q;
    beta = 0.5 * (1.f - d / 2 * sin(theta) / (1.f + d / 2 * sin(theta)));
    gamma = (0.5f + beta) * cos(theta);
    // Coefficients
    a1 = 0.5f + beta - gamma;
    a0 = a1 / 2;
    a2 = a0;
    b1 = -2 * gamma;
    b2 = 2 * beta;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] + a2 * inputs[2] - b1 * outputs[1] - b2 * outputs[2];
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
    theta = M_TWOPI * cutoff / sampleRate;
    d = 1 / Q;
    beta = 0.5 * (1.f - d / 2 * sin(theta)) / (1.f + d / 2 * sin(theta));
    gamma = (0.5f + beta) * cos(theta);
    // Coefficients
    a1 = -(0.5f + beta + gamma);
    a0 = -a1 / 2;
    a2 = a0;
    b1 = -2 * gamma;
    b2 = 2 * beta;
    // Finite difference equation
    output = a0 * inputs[0] + a1 * inputs[1] + a2 * inputs[2] - b1 * outputs[1] - b2 * outputs[2];
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
    theta = M_TWOPI * cutoff / sampleRate;
    argtan = theta / (2 * Q);
    if (argtan >= 0.999 * M_PI / 2)
        argtan = 0.999 * M_PI / 2;
    beta = 0.5 * (1.f - tan(argtan)) / (1.f + tan(argtan));
    gamma = (0.5f + beta) * cos(theta);
    // Coefficients
    a0 = 0.5 - beta;
    a2 = -a0;
    b1 = -2 * gamma;
    b2 = 2 * beta;
    // Finite difference equation
    output = a0 * inputs[0] + a2 * inputs[2] - b1 * outputs[1] - b2 * outputs[2];
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