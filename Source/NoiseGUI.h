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
    juce::ComboBox filterMenu;
    juce::Slider cutoffSlider, resonanceSlider, gainSlider, levelSlider;
    juce::ToggleButton bypassButton, filterBypassButton;
    juce::Label cutoffLabel, resonanceLabel, gainLabel, levelLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterChoice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment, resonanceAttachment, gainAttachment, levelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment, filterBypassAttachment;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGUI)
};
