/*
  ==============================================================================

    EffectsGUI.cpp
    Created: 30 May 2022 7:22:16pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OverdriveGUI.h"

//==============================================================================
OverdriveGUI::OverdriveGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(250, 220);

    odMenu.addItem("Overdrive", 1);
    odMenu.addItem("Distortion", 2);
    odMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&odMenu);

    odGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    odGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    odGainSlider.setRange(1.f, 10.f);
    odGainSlider.setValue(1.f);
    odGainSlider.setTextValueSuffix(" dB");
    odGainSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&odGainSlider);
    odGainLabel.setText("Gain", juce::dontSendNotification);
    odGainLabel.attachToComponent(&odGainSlider, false);
    odGainLabel.setJustificationType(juce::Justification::centredTop);
    odGainLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&odGainLabel);

    odWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    odWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    odWetSlider.setRange(0.f, 1.f);
    odWetSlider.setValue(0.f);
    odWetSlider.setTextValueSuffix(" %");
    odWetSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&odWetSlider);
    odWetLabel.setText("Wet", juce::dontSendNotification);
    odWetLabel.attachToComponent(&odWetSlider, false);
    odWetLabel.setJustificationType(juce::Justification::centredTop);
    odWetLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&odWetLabel);

    odGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "odGain", odGainSlider);
    odWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "odWet", odWetSlider);
    odChoice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "odType", odMenu);

}

OverdriveGUI::~OverdriveGUI()
{
}

void OverdriveGUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::orange);
    g.setFont(18.);
    g.drawText("Overdrive", 82, 20, 100, 25, juce::Justification::centredTop);

    // Horizontal lines
    g.drawLine(0., 0., 250., 0., 1.5);
    g.drawLine(0., 220., 250., 220., 3.);
    // Vertical lines
    g.drawLine(0., 0., 0., 220., 3.);
    g.drawLine(250., 0., 250., 220., 1.5);
    
}

void OverdriveGUI::resized()
{
    odMenu.setBounds(25, 45, 200, 25);
    odGainSlider.setBounds(30, 120, 80, 80);
    odWetSlider.setBounds(140, 120, 80, 80);

}
