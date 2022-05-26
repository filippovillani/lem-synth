/*
  ==============================================================================

    myOSC.h
    Created: 26 May 2022 2:54:34pm
    Author:  User

  ==============================================================================
*/

#pragma once

#ifndef PI
#define PI  3.1415926535897932384626433832795
#endif
#ifndef TWOPI
#define TWOPI 6.283185307179586476925286766559
#endif

#include <iostream>
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

