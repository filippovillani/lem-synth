/*
  ==============================================================================

    myAudioLibrary.h
    Created: 31 May 2022 4:24:01pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <cmath>
#include <random>


#ifndef PI
#define M_PI  3.1415926535897932384626433832795
#endif
#define M_TWOPI 6.283185307179586476925286766559
#define M_SQRT2 1.414213562373095048801

// =============== OVERDRIVE ===================
class myODfx {
    double input;
    double output;

    double xM;

    double wet;


public:
    double overdrive(double input, float gain, float wet);
    double distortion(double input, float gain, float wet);
};

// =============== ENVELOPE ===================
class myEnvelope {
    double output;
    double input;
    double curramp;
    double attack, decay, sustain, release, shape;
    int aphase, dphase, sphase, rphase;

public:
    int trigger;
    float sampleRate;

    double adsr(double input, int trigger);
    void setAttack(double attack_ms);
    void setRelease(double release_ms);
    void setDecay(double decay_ms);
    void setSustain(double sustain_level); // sustain_level must be in (0, 1]
};


// =============== FILTERS ===================
class myFilter {
public:
    float sampleRate;

    double LPF1ord(double input, float cutoff);
    double HPF1ord(double input, float cutoff);
    double LPF2ord(double input, float cutoff, float Q);
    double HPF2ord(double input, float cutoff, float Q);
    double BPF2ord(double input, float cutoff, float Q);
    double LPShelving(double input, float cutoff, float gain_lin);
    double HPShelving(double input, float cutoff, float gain_lin);
    double Peak(double input, float cutoff, float Q, float gain_lin);


private:
    double inputs[3] = { 0 };
    double outputs[3] = { 0 };

    double output;
    
    // Parameters
    double k;

    double b0, b1, b2;
    double a1, a2;

};


// =============== OSCILLATORS ===================
class myOsc {
    double phase;
    double output;
    float u1;
    float u2;
    float phi;
    float r;


public:
    float sampleRate;

    myOsc();

    double sine(double frequency);
    double square(double frequency);
    double saw(double frequency);
    double triangle(double frequency);
    double noise();
};
