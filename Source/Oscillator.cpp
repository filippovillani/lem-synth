/*
  ==============================================================================

    Oscillator.cpp
    Created: 25 May 2022 2:45:26pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(LEMSynthAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(300, 200);
    // OSC 1
    osc1Menu.addItem("Sine", 1);
    osc1Menu.addItem("Saw", 2);
    osc1Menu.addItem("Square", 3);
    osc1Menu.addItem("Triangle", 4);
    osc1Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc1Menu);

    oscMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    oscMixSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 30, 18);
    oscMixSlider.setRange(0.f, 100.f);
    oscMixSlider.setValue(0.f);
    oscMixSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&oscMixSlider);

    octShiftSlider1.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    octShiftSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 38, 25);
    octShiftSlider1.setTextValueSuffix(" oct");
    octShiftSlider1.setRange(-2, 2, 1);
    octShiftSlider1.setValue(0);
    addAndMakeVisible(&octShiftSlider1);

    detuneSlider1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider1.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    detuneSlider1.setRange(-100, 100);
    detuneSlider1.setTextValueSuffix(" cents");
    detuneSlider1.setValue(0);
    detuneSlider1.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&detuneSlider1);

    // OSC 2
    osc2Menu.addItem("Sine", 1);
    osc2Menu.addItem("Saw", 2);
    osc2Menu.addItem("Square", 3);
    osc2Menu.addItem("Triangle", 4);
    osc2Menu.addItem("Noise", 5);
    osc2Menu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&osc2Menu);

    octShiftSlider2.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    octShiftSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 38, 25);
    octShiftSlider2.setTextValueSuffix(" oct");
    octShiftSlider2.setRange(-2, 2, 1);
    octShiftSlider2.setValue(0);
    addAndMakeVisible(&octShiftSlider2);

    detuneSlider2.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    detuneSlider2.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    detuneSlider2.setRange(-100, 100);
    detuneSlider2.setTextValueSuffix(" cents");
    detuneSlider2.setValue(0);
    detuneSlider2.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&detuneSlider2);

    // Attachments
    osc1Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc1Type", osc1Menu);
    oscMixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oscMix", oscMixSlider);
    osc2Choice = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "osc2Type", osc2Menu);
    octShiftAttachment1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oct1", octShiftSlider1);
    octShiftAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "oct2", octShiftSlider2);
    detuneAttachment1 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "detune1", detuneSlider1);
    detuneAttachment2 = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "detune2", detuneSlider2);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Oscillators", titleArea, juce::Justification::centredTop);

    g.drawText("OSC1", 50, 32, 100, 20, juce::Justification::centredTop);
    g.drawText("OSC2", 50, 105, 100, 20, juce::Justification::centredTop);

    juce::Rectangle <float> area(25, 25, 175, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    osc1Menu.setBounds(50, 48, 100, 22);
    oscMixSlider.setBounds(50, 75, 100, 20);
    osc2Menu.setBounds(50, 121, 100, 22);
    octShiftSlider1.setBounds(157, 52, 40, 30);
    octShiftSlider2.setBounds(157, 125, 40, 30);
    detuneSlider1.setBounds(200, 52, 70, 70);
    detuneSlider2.setBounds(200, 125, 70, 70);
}

