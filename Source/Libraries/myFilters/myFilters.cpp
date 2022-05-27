/*
  ==============================================================================

    PipoFilters.cpp
    Created: 10 Nov 2021 4:29:14pm
    Author:  Filippo Villani

    Based on Will Pirkle's work.

  ==============================================================================
*/

#include "myFilters.h"

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