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
    setSize(1200, 500);
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
}


void LEMSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    oscGUI.setBounds(0, 0, 600, 250);
    envGUI.setBounds(600, 0, 600, 250);
    odGUI.setBounds(0, 250, 300, 250);
    noiseGUI.setBounds(300, 250, 300, 250);
    filterGUI.setBounds(600, 250, 300, 250);
    mtGUI.setBounds(900, 250, 300, 250);

}
