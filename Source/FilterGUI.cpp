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

    filterMenu.addItem("LPF2ord", 1);
    filterMenu.addItem("BPF2ord", 2);
    filterMenu.addItem("HPF2ord", 3);
    filterMenu.addItem("LPF1ord", 4);
    filterMenu.addItem("HPF1ord", 5);
    filterMenu.addItem("LPShelv", 6);
    filterMenu.addItem("HPShelv", 7);
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
    cutoffLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
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
    resonanceLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&resonanceLabel);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    gainSlider.setRange(-60.f, 18.f);
    gainSlider.setValue(0.f);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setNumDecimalPlacesToDisplay(1);
    addAndMakeVisible(&gainSlider);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centredTop);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&gainLabel);

    
    bypassButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    bypassButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    bypassButton.setClickingTogglesState(true);
    addAndMakeVisible(&bypassButton);

    filterChoice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "filterType", filterMenu);
    cutoffAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "cutoff", cutoffSlider);
    resonanceAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "resonance", resonanceSlider);
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "filterGain", gainSlider);
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.apvts, "filterBypass", bypassButton);

}

FilterGUI::~FilterGUI()
{
}

void FilterGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::orange);
    g.setFont(18.);
    g.drawText("FILTER", 82, 15, 100, 25, juce::Justification::centredTop);

    // Horizontal lines
    g.drawLine(0., 0., 250., 0., 1.5);
    g.drawLine(0., 220., 250., 220., 3.);
    // Vertical lines
    g.drawLine(0., 0., 0., 220., 1.5);
    g.drawLine(250., 0., 250., 220., 1.5);
}


void FilterGUI::resized()
{
    filterMenu.setBounds(40, 45, 170, 25);
    cutoffSlider.setBounds(20, 130, 70, 70);
    resonanceSlider.setBounds(93, 130, 70, 70);
    gainSlider.setBounds(166, 130, 70, 70);
    bypassButton.setBounds(7, 10, 30, 30);
}

