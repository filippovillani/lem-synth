/*
  ==============================================================================

    Oscillator.h
    Created: 25 May 2022 2:45:26pm
    Author:  User

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator : public juce::Component
{
public:
    Oscillator(LEMSynthAudioProcessor&);
    ~Oscillator() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox osc1Menu, osc2Menu;
    juce::Slider osc1GainSlider, osc2GainSlider;
    juce::Slider octShiftSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1Choice, osc2Choice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> osc1GainAttachment, osc2GainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> octShiftAttachment;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};

