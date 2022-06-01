/*
  ==============================================================================

    Oscillator.cpp
    Created: 25 May 2022 2:45:26pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorGUI.h"

//==============================================================================
OscillatorGUI::OscillatorGUI(LEMSynthAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(500, 220);
    // OSC 1
    osc1Menu.addItem("Sine", 1);
    osc1Menu.addItem("Saw", 2);
    osc1Menu.addItem("Square", 3);
    osc1Menu.addItem("Triangle", 4);
    osc1Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc1Menu);

    oscMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 20);
    oscMixSlider.setRange(0.f, 100.f);
    oscMixSlider.setValue(0.f);
    oscMixSlider.setNumDecimalPlacesToDisplay(0);
    oscMixSlider.setColour(1, juce::Colours::red);
    addAndMakeVisible(&oscMixSlider);
    oscMixLabel.setText("OSC2 Blend", juce::dontSendNotification);
    oscMixLabel.attachToComponent(&oscMixSlider, false);
    oscMixLabel.setJustificationType(juce::Justification::centredTop);
    oscMixLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&oscMixLabel);

    octShiftSlider1.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    octShiftSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 38, 25);
    octShiftSlider1.setTextValueSuffix(" oct");
    octShiftSlider1.setRange(-2, 2, 1);
    octShiftSlider1.setValue(0);
    addAndMakeVisible(&octShiftSlider1);
    octLabel1.setText("Octave1", juce::dontSendNotification);
    octLabel1.attachToComponent(&octShiftSlider1, false);
    octLabel1.setJustificationType(juce::Justification::centredTop);
    octLabel1.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&octLabel1);

    detuneSlider1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 57, 20);
    detuneSlider1.setRange(-100, 100);
    detuneSlider1.setTextValueSuffix(" cents");
    detuneSlider1.setValue(0);
    detuneSlider1.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&detuneSlider1);
    detuneLabel1.setText("Detune1", juce::dontSendNotification);
    detuneLabel1.attachToComponent(&detuneSlider1, false);
    detuneLabel1.setJustificationType(juce::Justification::centredTop);
    detuneLabel1.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&detuneLabel1);

    // OSC 2
    osc2Menu.addItem("Sine", 1);
    osc2Menu.addItem("Saw", 2);
    osc2Menu.addItem("Square", 3);
    osc2Menu.addItem("Triangle", 4);
    osc2Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc2Menu);

    octShiftSlider2.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    octShiftSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 38, 25);
    octShiftSlider2.setTextValueSuffix(" oct");
    octShiftSlider2.setRange(-2, 2, 1);
    octShiftSlider2.setValue(0);
    addAndMakeVisible(&octShiftSlider2);
    octLabel2.setText("Octave2", juce::dontSendNotification);
    octLabel2.attachToComponent(&octShiftSlider2, false);
    octLabel2.setJustificationType(juce::Justification::centredTop);
    octLabel2.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&octLabel2);

    detuneSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 57, 20);
    detuneSlider2.setRange(-100, 100);
    detuneSlider2.setTextValueSuffix(" cents");
    detuneSlider2.setValue(0);
    detuneSlider2.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&detuneSlider2);
    detuneLabel2.setText("Detune2", juce::dontSendNotification);
    detuneLabel2.attachToComponent(&detuneSlider2, false);
    detuneLabel2.setJustificationType(juce::Justification::centredTop);
    detuneLabel2.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&detuneLabel2);

    // Attachments
    osc1Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc1Type", osc1Menu);
    oscMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oscMix", oscMixSlider);
    osc2Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc2Type", osc2Menu);
    octShiftAttachment1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oct1", octShiftSlider1);
    octShiftAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oct2", octShiftSlider2);
    detuneAttachment1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "detune1", detuneSlider1);
    detuneAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "detune2", detuneSlider2);
}

OscillatorGUI::~OscillatorGUI()
{
}

void OscillatorGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setFont(18.);
    g.setColour(juce::Colours::orange);
    g.drawText("OSC1", 82, 22, 100, 25, juce::Justification::centredTop);
    g.drawText("OSC2", 312, 22, 100, 25, juce::Justification::centredTop);

    // Horizontal lines
    g.drawLine(0., 0., 500., 0., 3.);
    g.drawLine(0., 220., 500., 220., 1.5);
    // Vertical lines
    g.drawLine(0., 0., 0., 220., 3.);
    g.drawLine(500., 0., 500., 220., 1.5);
}

void OscillatorGUI::resized()
{

    osc1Menu.setBounds(50, 56, 170, 25);
    osc2Menu.setBounds(280, 56, 170, 25);

    oscMixSlider.setBounds(206, 107, 90, 90);
    
    detuneSlider1.setBounds(125, 135, 75, 75);
    detuneSlider2.setBounds(370, 135, 75, 75);

    octShiftSlider1.setBounds(65, 154, 50, 45);
    octShiftSlider2.setBounds(310, 154, 50, 45);

}

