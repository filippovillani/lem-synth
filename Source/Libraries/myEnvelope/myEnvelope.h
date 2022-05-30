/*
  ==============================================================================

    myEnvelope.h
    Created: 27 May 2022 12:16:32pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include "math.h"

#ifndef PI
#define M_PI  3.1415926535897932384626433832795
#endif
#define M_TWOPI 6.283185307179586476925286766559

class myEnvelope {
    double output;
    float curramp;
    double attack, decay, sustain, release;
    int aphase, dphase, sphase, rphase;


    double input;
    //double output;
    //double attack;
    //double decay;
    //double sustain;
    //double release;
    double amplitude;
    long holdtime = 1;
    long holdcount;
    int attackphase, decayphase, sustainphase, releasephase;

public:
    int trigger;
    float sampleRate;

    double adsr(double input, int trigger);
    void setAttack(double attack_ms);
    void setRelease(double release_ms);
    void setDecay(double decay_ms);
    void setSustain(double sustain_level); // sustain_level must be in (0, 1]
};