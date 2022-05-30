/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LEMSynthAudioProcessor::LEMSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
}

LEMSynthAudioProcessor::~LEMSynthAudioProcessor()
{
}

//==============================================================================
const juce::String LEMSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LEMSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LEMSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LEMSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LEMSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LEMSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LEMSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LEMSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LEMSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void LEMSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LEMSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void LEMSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LEMSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LEMSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    for (int i = 0; i < mySynth.getNumVoices(); i++) {
        //if myVoice successfully casts as a SynthVoice*, get the voice and set the params
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))) {

            myVoice->getOscParams(
                apvts.getRawParameterValue("osc1Type"),
                apvts.getRawParameterValue("osc1Gain"),
                apvts.getRawParameterValue("osc2Type"),
                apvts.getRawParameterValue("osc2Gain"),
                apvts.getRawParameterValue("oct1"),
                apvts.getRawParameterValue("oct2"));

            myVoice->getEnvelopeParams(
                apvts.getRawParameterValue("attack"),
                apvts.getRawParameterValue("decay"),
                apvts.getRawParameterValue("sustain"),
                apvts.getRawParameterValue("release"));

            myVoice->getFilterParams(
                apvts.getRawParameterValue("filterType"),
                apvts.getRawParameterValue("cutoff"),
                apvts.getRawParameterValue("resonance"),
                apvts.getRawParameterValue("filterBypass"));

            myVoice->getODParams(
                apvts.getRawParameterValue("odType"),
                apvts.getRawParameterValue("odGain"),
                apvts.getRawParameterValue("odWet"));

            myVoice->getOtherParams(
                apvts.getRawParameterValue("masterGain"));
        }
    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool LEMSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LEMSynthAudioProcessor::createEditor()
{
    return new LEMSynthAudioProcessorEditor (*this);
}

//==============================================================================
void LEMSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LEMSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LEMSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout
LEMSynthAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    // Oscillator's parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("osc1Type", "Osc1 Type", juce::StringArray("Sine", "Saw", "Square", "Triangle"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("osc1Gain", "Osc1 Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("osc2Type", "Osc2 Type", juce::StringArray("Sine", "Saw", "Square", "Triangle", "Noise"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("osc2Gain", "Osc2 Gain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("oct1", "Octave Shift 1", -2, 2, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("oct2", "Octave Shift 2", -2, 2, 0));
    // Envelope's parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("attack", "Attack", juce::NormalisableRange<float>(5.f, 5000.f, 1.f), 1.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("decay", "Decay", juce::NormalisableRange<float>(5.f, 5000.f, 1.f), 5.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("sustain", "Sustain", juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("release", "Release", juce::NormalisableRange<float>(5.f, 5000.f, 1.f), 5.f));
    // Filter's parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("filterType", "Filter Type", juce::StringArray("LPF", "BPF", "HPF"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("cutoff", "CutOff", juce::NormalisableRange<float>(80.f, 20000.f, 1.f, 0.4f), 80.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("resonance", "Q", juce::NormalisableRange<float>(0.1f, 10.f, 0.1f), 0.707f));
    params.push_back(std::make_unique<juce::AudioParameterBool>("filterBypass", "Filter Bypass", false));
    // OD's parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>("odType", "OD Type", juce::StringArray("Overdrive", "Distortion"), 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("odGain", "OD Gain", juce::NormalisableRange<float>(-6.f, 18.f, 0.1f), 0.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("odWet", "OD Wet", juce::NormalisableRange<float>(0.f, 100.f, 1.f), 0.f));

    // Other parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>("masterGain", "Master Gain", juce::NormalisableRange<float>(-60.f, 12.f, 0.1f), -6.f));

    return { params.begin(), params.end() };
}