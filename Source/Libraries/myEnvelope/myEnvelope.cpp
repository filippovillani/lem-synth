/*
  ==============================================================================

    myEnvelope.cpp
    Created: 27 May 2022 12:16:32pm
    Author:  User

  ==============================================================================
*/

#include "myEnvelope.h"

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
