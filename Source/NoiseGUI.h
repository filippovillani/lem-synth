/*
  ==============================================================================

    NoiseGUI.h
    Created: 31 May 2022 7:47:40pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class NoiseGUI  : public juce::Component
{
public:
    NoiseGUI(LEMSynthAudioProcessor&);
    ~NoiseGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGUI)
};
