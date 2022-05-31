/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "OscillatorGUI.h"
#include "EnvelopeGUI.h"
#include "FilterGUI.h"
#include "OverdriveGUI.h"
#include "MasterGUI.h"
#include "NoiseGUI.h"

//==============================================================================
/**
*/
class LEMSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LEMSynthAudioProcessorEditor (LEMSynthAudioProcessor&);
    ~LEMSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LEMSynthAudioProcessor& audioProcessor;

    OscillatorGUI oscGUI;
    EnvelopeGUI envGUI;
    OverdriveGUI odGUI;
    NoiseGUI noiseGUI;
    FilterGUI filterGUI;
    MasterGUI mtGUI;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LEMSynthAudioProcessorEditor)
};
