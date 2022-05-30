/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"
#include "OtherStuff.h"
#include "EffectsGUI.h"

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

    Oscillator oscGUI;
    Envelope envGUI;
    Filter filterGUI;
    OtherStuff mainGUI;
    EffectsGUI effectsGUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LEMSynthAudioProcessorEditor)
};
