#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
    //attackSlider.setNumDecimalPlacesToDisplay(1);
    //attackSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&attackSlider);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.5f, 5000.f);
    releaseSlider.setValue(0.5f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
    //releaseSlider.setNumDecimalPlacesToDisplay(1);
    //releaseSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&releaseSlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
    //sustainSlider.setNumDecimalPlacesToDisplay(1);
    //sustainSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&sustainSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.f, 5000.f);
    decaySlider.setValue(1.f);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60.0, 20.0);
    //decaySlider.setNumDecimalPlacesToDisplay(1);
    //decaySlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&decaySlider);

    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);

}

Envelope::~Envelope()
{
}

void Envelope::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope", titleArea, juce::Justification::centredTop);

    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(25, 25, 150, 150, 20.f, 2.f);

    // To fix in the future
    g.setFont(20);
    g.drawText("P", 180, 10, 30, 30, juce::Justification::centredTop);
    g.drawText("i", 180, 30, 30, 30, juce::Justification::centredTop);
    g.drawText("p", 180, 50, 30, 30, juce::Justification::centredTop);
    g.drawText("o", 180, 70, 30, 30, juce::Justification::centredTop);
    g.drawText("S", 180, 90, 30, 30, juce::Justification::centredTop);
    g.drawText("y", 180, 110, 30, 30, juce::Justification::centredTop);
    g.drawText("n", 180, 130, 30, 30, juce::Justification::centredTop);
    g.drawText("t", 180, 150, 30, 30, juce::Justification::centredTop);
    g.drawText("h", 180, 170, 30, 30, juce::Justification::centredTop);

}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}
