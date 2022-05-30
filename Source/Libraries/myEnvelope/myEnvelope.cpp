/*
  ==============================================================================

    myEnvelope.cpp
    Created: 27 May 2022 12:16:32pm
    Author:  User

  ==============================================================================
*/

#include "myEnvelope.h"

double myEnvelope::adsr(double input, int trigger) {
    if (trigger == 1 && attackphase != 1 && sustainphase != 1 && decayphase != 1) {
        holdcount = 0;
        decayphase = 0;
        sustainphase = 0;
        releasephase = 0;
        attackphase = 1;
    }

    if (attackphase == 1) {
        releasephase = 0;
        amplitude += attack;
        output = input * amplitude;

        if (amplitude >= 0.99999) {
            amplitude = 1.;
            attackphase = 0;
            decayphase = 1;
        }
    }


    if (decayphase == 1) {
        amplitude *= decay;
        output = input * amplitude;
        if (amplitude <= sustain) {
            amplitude = sustain;
            decayphase = 0;
            sustainphase = 1;
        }
    }


    if (sustainphase == 1) {
        output = input * amplitude;

        if (trigger != 1) {
            sustainphase = 0;
            releasephase = 1;
        }
    }
 

    if (releasephase == 1 && amplitude > 0.) {
        amplitude *= release;
        output = input * amplitude;

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
