#include <JuceHeader.h>
#include "EnvelopeGUI.h"

//==============================================================================
EnvelopeGUI::EnvelopeGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(500, 220);
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    attackSlider.setRange(5.f, 5000.f);
    attackSlider.setValue(5.f);
    attackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    attackSlider.setNumDecimalPlacesToDisplay(0);
    attackSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&attackSlider);
    attackLabel.setText("A", juce::dontSendNotification);
    attackLabel.attachToComponent(&attackSlider, true);
    attackLabel.setJustificationType(juce::Justification::centredTop);
    attackLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&attackLabel);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    decaySlider.setRange(5.f, 5000.f);
    decaySlider.setValue(5.f);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    decaySlider.setNumDecimalPlacesToDisplay(0);
    decaySlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&decaySlider);
    decayLabel.setText("D", juce::dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, true);
    decayLabel.setJustificationType(juce::Justification::centredTop);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&decayLabel);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    sustainSlider.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&sustainSlider);
    sustainLabel.setText("S", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sustainSlider, true);
    sustainLabel.setJustificationType(juce::Justification::centredTop);
    sustainLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&sustainLabel);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    releaseSlider.setRange(5.f, 5000.f);
    releaseSlider.setValue(5.f);
    releaseSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 65, 20);
    releaseSlider.setNumDecimalPlacesToDisplay(0);
    releaseSlider.setTextValueSuffix(" ms");
    addAndMakeVisible(&releaseSlider);
    releaseLabel.setText("R", juce::dontSendNotification);
    releaseLabel.attachToComponent(&releaseSlider, true);
    releaseLabel.setJustificationType(juce::Justification::centredTop);
    releaseLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&releaseLabel);

    shapeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    shapeSlider.setRange(0.001f, 0.1f);
    shapeSlider.setValue(0.1f);
    shapeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 65, 20);
    shapeSlider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(&shapeSlider);
    shapeLabel.setText("Shape", juce::dontSendNotification);
    shapeLabel.attachToComponent(&shapeSlider, false);
    shapeLabel.setJustificationType(juce::Justification::centredTop);
    shapeLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    addAndMakeVisible(&shapeLabel);



    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "attack", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "decay", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "sustain", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "release", releaseSlider);
    shapeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "shape", shapeSlider);


}

EnvelopeGUI::~EnvelopeGUI()
{
}

void EnvelopeGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::orange);
    g.setFont(18.);
    g.drawText("ENVELOPE", 200, 20, 100, 25, juce::Justification::centredTop);

    // Horizontal lines
    g.drawLine(0., 0., 500., 0., 3.);
    g.drawLine(0., 220., 500., 220., 1.5);
    // Vertical lines
    g.drawLine(0., 0., 0., 220., 1.5);
    g.drawLine(500., 0., 500., 220., 3.);

}

void EnvelopeGUI::resized()
{
    attackSlider.setBounds  (120,  60,  250, 30); 
    decaySlider.setBounds   (120, 100,  250, 30);
    sustainSlider.setBounds (120, 140, 250,  30);
    releaseSlider.setBounds (120, 180, 250,  30);
    shapeSlider.setBounds   (410,  60,  50, 150);
}
