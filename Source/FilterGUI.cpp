/*
  ==============================================================================

    Filter.cpp
    Created: 25 May 2022 2:45:14pm
    Author:  User

  ==============================================================================
*/


#include <JuceHeader.h>
#include "FilterGUI.h"

//==============================================================================
FilterGUI::FilterGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(250, 220);

    filterMenu.addItem("LPF", 1);
    filterMenu.addItem("BPF", 2);
    filterMenu.addItem("HPF", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterMenu);

    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    cutoffSlider.setRange(80.f, 20000.f);
    cutoffSlider.setSkewFactor(0.4f);
    cutoffSlider.setValue(80.f);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&cutoffSlider);
    cutoffLabel.setText("Freq", juce::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffSlider, false);
    cutoffLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(&cutoffLabel);

    resonanceSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    resonanceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    resonanceSlider.setRange(0.1f, 10.f);
    resonanceSlider.setValue(0.707f);
    resonanceSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&resonanceSlider);
    resonanceLabel.setText("Q", juce::dontSendNotification);
    resonanceLabel.attachToComponent(&resonanceSlider, false);
    resonanceLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible(&resonanceLabel);

    bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    bypassButton.setClickingTogglesState(true);
    addAndMakeVisible(&bypassButton);

    filterChoice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "filterType", filterMenu);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "cutoff", cutoffSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "resonance", resonanceSlider);
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "filterBypass", bypassButton);


}

FilterGUI::~FilterGUI()
{
}

void FilterGUI::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}


void FilterGUI::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    cutoffSlider.setBounds(30, 100, 70, 70);
    resonanceSlider.setBounds(100, 100, 70, 70);
    bypassButton.setBounds(90, 80, 30, 30);
}

