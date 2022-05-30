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
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;

    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    mainGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    effectsGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));

}
