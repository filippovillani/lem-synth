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
class OverdriveGUI : public juce::Component
{
public:
    OverdriveGUI(LEMSynthAudioProcessor&);
    ~OverdriveGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox odMenu;
    
    juce::Slider odGainSlider, odWetSlider;
    juce::Label odGainLabel, odWetLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> odGainAttachment, odWetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> odChoice;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveGUI)
};
