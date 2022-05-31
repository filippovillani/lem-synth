/*
  ==============================================================================

    myEffects.h
    Created: 30 May 2022 6:12:03pm
    Author:  User

  ==============================================================================
*/

#pragma once
#include <cmath>
#include <JuceHeader.h>

#ifndef PI
#define M_PI  3.1415926535897932384626433832795
#endif
#define M_TWOPI 6.283185307179586476925286766559

class myODfx {
    double output;
    double xM;
    double wet;

public:
    double overdrive(double input, float gain, float wet);
    double distortion(double input, float gain, float wet);
};

class myMODfx {
    double output;

    unsigned int D0; // ritardo base dei campioni
    unsigned int D1; // ritardo variabile

public:
    double flanger(double input, float freq, float depth, float wet, juce::AudioBuffer<float> buffer);


};