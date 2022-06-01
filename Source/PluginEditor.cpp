/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LEMSynthAudioProcessorEditor::LEMSynthAudioProcessorEditor (LEMSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p), envGUI(p), filterGUI(p), mtGUI(p), odGUI(p), noiseGUI(p)
{
    setSize(1000, 440);
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&mtGUI);
    addAndMakeVisible(&odGUI);
    addAndMakeVisible(&noiseGUI);
}

LEMSynthAudioProcessorEditor::~LEMSynthAudioProcessorEditor()
{
}

//==============================================================================
void LEMSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::orange);

}


void LEMSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    oscGUI.setBounds    (  0,   0, 500, 220);
    envGUI.setBounds    (500,   0, 500, 220);
    odGUI.setBounds     (  0, 220, 250, 220);
    noiseGUI.setBounds  (250, 220, 250, 220);
    filterGUI.setBounds (500, 220, 250, 220);
    mtGUI.setBounds     (750, 220, 250, 220);

}
