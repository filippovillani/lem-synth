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
class OscillatorGUI : public juce::Component
{
public:
    OscillatorGUI(LEMSynthAudioProcessor&);
    ~OscillatorGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:

    juce::ComboBox osc1Menu, osc2Menu;
    juce::Slider oscMixSlider;
    juce::Slider octShiftSlider1, octShiftSlider2;
    juce::Slider detuneSlider1, detuneSlider2;

    juce::Label detuneLabel1, detuneLabel2,
        octLabel1, octLabel2,
        oscMixLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> osc1Choice, osc2Choice;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscMixAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> octShiftAttachment1, octShiftAttachment2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> detuneAttachment1, detuneAttachment2;

    LEMSynthAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorGUI)
};

