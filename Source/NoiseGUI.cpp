/*
  ==============================================================================

    NoiseGUI.cpp
    Created: 31 May 2022 7:47:40pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NoiseGUI.h"

//==============================================================================
NoiseGUI::NoiseGUI(LEMSynthAudioProcessor& p) : audioProcessor(p)
{
    setSize(250, 220);

}

NoiseGUI::~NoiseGUI()
{
}

void NoiseGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("NoiseGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void NoiseGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
