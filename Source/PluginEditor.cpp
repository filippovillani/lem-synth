/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LEMSynthAudioProcessorEditor::LEMSynthAudioProcessorEditor (LEMSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGUI(p), envGUI(p), filterGUI(p), mainGUI(p), effectsGUI(p)
{
    setSize(1000, 200);
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
    addAndMakeVisible(&mainGUI);
    addAndMakeVisible(&effectsGUI);
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

    oscGUI.setBounds(0, 0, 300, 200);
    envGUI.setBounds(300, 0, 200, 200);
    filterGUI.setBounds(500, 0, 200, 200);
    mainGUI.setBounds(700, 0, 100, 200);
    effectsGUI.setBounds(800, 0, 200, 200);

}
