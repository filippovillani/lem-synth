/*
  ==============================================================================

    Envelope.h
    Created: 25 May 2022 2:45:04pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class EnvelopeGUI : public juce::Component
{
public:
    EnvelopeGUI(LEMSynthAudioProcessor&);
    ~EnvelopeGUI() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider
        attackSlider,
        decaySlider,
        sustainSlider,
        releaseSlider,
        shapeSlider;

    juce::Label 
        attackLabel,
        decayLabel,
        sustainLabel,
        releaseLabel,
        shapeLabel;


    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
        attackAttachment,
        decayAttachment,
        sustainAttachment,
        releaseAttachment,
        shapeAttachment;

    LEMSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnvelopeGUI)
};

