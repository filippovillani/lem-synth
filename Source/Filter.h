/*
  ==============================================================================

    Filter.h
    Created: 25 May 2022 2:45:14pm
    Author:  User

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter : public juce::Component
{
public:
    Filter(LEMSynthAudioProcessor&);
    ~Filter() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterMenu;
    juce::Slider cutoffSlider, resonanceSlider;
    juce::ToggleButton bypassButton;
    juce::Label cutoffLabel, resonanceLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterChoice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment, resonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
