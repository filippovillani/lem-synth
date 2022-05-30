/*
  ==============================================================================

    EffectsGUI.cpp
    Created: 30 May 2022 7:22:16pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EffectsGUI.h"

//==============================================================================
EffectsGUI::EffectsGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    odGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    odGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    odGainSlider.setRange(1.f, 10.f);
    odGainSlider.setValue(1.f);
    odGainSlider.setTextValueSuffix(" eo");
    odGainSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&odGainSlider);
    odGainLabel.setText("Gain", juce::dontSendNotification);
    odGainLabel.attachToComponent(&odGainSlider, false);
    odGainLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(&odGainLabel);

    odWetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    odWetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    odWetSlider.setRange(0.f, 1.f);
    odWetSlider.setValue(0.f);
    odWetSlider.setTextValueSuffix(" %");
    odWetSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&odWetSlider);
    odWetLabel.setText("Gain", juce::dontSendNotification);
    odWetLabel.attachToComponent(&odWetSlider, false);
    odWetLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(&odWetLabel);

    odGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "odGain", odGainSlider);
    odWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "odWet", odWetSlider);


}

EffectsGUI::~EffectsGUI()
{
}

void EffectsGUI::paint (juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("OD", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void EffectsGUI::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    odGainSlider.setBounds(30, 100, 70, 70);
    odWetSlider.setBounds(100, 100, 70, 70);

}
