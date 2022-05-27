/*
  ==============================================================================

    myOSC.h
    Created: 26 May 2022 2:54:34pm
    Author:  User

  ==============================================================================
*/

#pragma once

#ifndef M_PI
#define M_PI  3.1415926535897932384626433832795
#endif
#ifndef M_TWOPI
#define M_TWOPI 6.283185307179586476925286766559
#endif

#include <random>

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

