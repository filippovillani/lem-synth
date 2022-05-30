/*
  ==============================================================================

    myEffects.cpp
    Created: 30 May 2022 6:12:03pm
    Author:  User

  ==============================================================================
*/

#include "myEffects.h"

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