/*
  ==============================================================================

    MasterGUI.cpp
    Created: 31 May 2022 7:25:40pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MasterGUI.h"

//==============================================================================
MasterGUI::MasterGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(250, 220);
    masterSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    masterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    masterSlider.setRange(-60.f, 12.f);
    masterSlider.setValue(-6.f);
    masterSlider.setTextValueSuffix(" dB");
    masterSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&masterSlider);

    masterAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "masterGain", masterSlider);

}

MasterGUI::~MasterGUI()
{
}

void MasterGUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(38, 10, 50, 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Master", titleArea, juce::Justification::centredTop);

    g.drawText("Gain", 35, 40, 55, 20, juce::Justification::centredTop);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(25, 25, 75, 150, 20.f, 2.f);
}

void MasterGUI::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    int sliderWidth = 48;
    int sliderHeight = 175;

    masterSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}