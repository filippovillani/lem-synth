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
    masterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 22);
    masterSlider.setRange(-60.f, 12.f);
    masterSlider.setValue(-6.f);
    masterSlider.setTextValueSuffix(" dB");
    masterSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&masterSlider);
    masterLabel.setText("Master Gain", juce::dontSendNotification);
    masterLabel.attachToComponent(&masterSlider, false);
    masterLabel.setJustificationType(juce::Justification::centredTop);
    masterLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&masterLabel);

    masterAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "masterGain", masterSlider);

}

MasterGUI::~MasterGUI()
{
}

void MasterGUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(38, 10, 50, 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::orange);

    // Horizontal lines
    g.drawLine(0., 0., 250., 0., 1.5);
    g.drawLine(0., 220., 250., 220., 3.);
    g.drawLine(0., 150., 250., 150., 3.);
    // Vertical lines
    g.drawLine(0., 0., 0., 220., 1.5);
    g.drawLine(250., 0., 250., 220., 2.);

    g.setFont(26.);
    g.drawText("LEMSynth", 25, 170, 200, 35, juce::Justification::centredTop);
}

void MasterGUI::resized()
{
    masterSlider.setBounds(65, 30, 120, 100);
}