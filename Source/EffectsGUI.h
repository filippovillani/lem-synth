/*
  ==============================================================================

    EffectsGUI.h
    Created: 30 May 2022 7:22:16pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class EffectsGUI  : public juce::Component
{
public:
    EffectsGUI(LEMSynthAudioProcessor&);
    ~EffectsGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Distortion section
    juce::ComboBox odMenu;
    
    juce::Slider odGainSlider, odWetSlider;
    juce::Label odGainLabel, odWetLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> odGainAttachment, odWetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> odChoice;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsGUI)
};
