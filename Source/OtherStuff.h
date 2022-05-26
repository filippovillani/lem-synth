#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OtherStuff : public juce::Component
{
public:
    OtherStuff(LEMSynthAudioProcessor&);
    ~OtherStuff() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider masterSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;

    LEMSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OtherStuff)
};
