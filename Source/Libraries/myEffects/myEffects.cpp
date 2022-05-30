/*
  ==============================================================================

    myEffects.cpp
    Created: 30 May 2022 6:12:03pm
    Author:  User

  ==============================================================================
*/

#include "myEffects.h"

double myODfx::overdrive(double input, double gain, double wet) {

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


    return (1 - wet) * input + wet * output;
}