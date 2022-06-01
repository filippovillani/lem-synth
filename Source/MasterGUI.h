/*
  ==============================================================================

    MasterGUI.h
    Created: 31 May 2022 7:25:40pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class MasterGUI  : public juce::Component
{
public:
    MasterGUI(LEMSynthAudioProcessor&);
    ~MasterGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider masterSlider;
    juce::Label masterLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterAttachment;

    LEMSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MasterGUI)
};
