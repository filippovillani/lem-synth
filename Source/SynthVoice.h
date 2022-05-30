#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "myFilters.h"
#include "myOSC.h"
#include "myEnvelope.h"
#include "myEffects.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    // ===========================================
    bool canPlaySound(juce::SynthesiserSound* sound) override {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }
    // ===========================================
    void getOscParams(std::atomic<float>* selection1, std::atomic<float>* level1,
        std::atomic<float>* selection2, std::atomic<float>* level2, std::atomic<float>* oct2) {
        osc1Wave = *selection1;
        osc1level = *level1;
        osc2Wave = *selection2;
        osc2level = *level2;
        octIdx = *oct2;
    }
    
    double setOscType() {
        osc1.sampleRate = getSampleRate();
        osc2.sampleRate = getSampleRate();
        switch (osc1Wave) {
        case 0:
            sample1 = osc1.sine(frequency);
            break;
        case 1:
            sample1 = osc1.saw(frequency);
            break;
        case 2:
            sample1 = osc1.square(frequency);
            break;
        case 3:
            sample1 = osc1.triangle(frequency);
            break;
        default:
            sample1 = osc1.sine(frequency);
            break;
        }

        switch (osc2Wave) {
        case 0:
            sample2 = osc2.sine(frequency * octShiftFreq[octIdx + 2]);
            break;
        case 1:
            sample2 = osc2.saw(frequency * octShiftFreq[octIdx + 2]);
            break;
        case 2:
            sample2 = osc2.square(frequency * octShiftFreq[octIdx + 2]);
            break;
        case 3:
            sample2 = osc2.triangle(frequency * octShiftFreq[octIdx + 2]);
            break;
        case 4:
            sample2 = osc2.noise();
            break;
        default:
            sample2 = osc2.sine(frequency * octShiftFreq[octIdx + 2]);
            break;
        }
        return (sample1 * osc1level + sample2 * osc2level) / 2;
    }
    // ===========================================
    void getEnvelopeParams(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release) {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    
    double setEnvelope() {
        env1.sampleRate = getSampleRate();
        return env1.adsr(setOscType(), env1.trigger);
    }
    // ==========================================
    void getFilterParams(std::atomic<float>* filterType, std::atomic<float>* filterCutoff, std::atomic<float>* filterRes, std::atomic<float>* onoff) {
        filterTypeParam = *filterType;
        cutoffParam = *filterCutoff;
        resonanceParam = *filterRes;
        filterBypass = *onoff;
    }

    double setFilter() {
        filter.sampleRate = getSampleRate();

        switch (filterTypeParam) {
        case 0:
            return filter.LPF2ord(setEnvelope(), cutoffParam, resonanceParam);
        case 1:
            return filter.BPF2ord(setEnvelope(), cutoffParam, resonanceParam);
        case 2:
            return filter.HPF2ord(setEnvelope(), cutoffParam, resonanceParam);

        default:
            return filter.LPF2ord(setEnvelope(), cutoffParam, resonanceParam);
        }
    }
    // ===========================================
    void getOtherParams(std::atomic<float>* gain) {
        masterGain = *gain;
    }

    // ===========================================

    void getODParams(std::atomic<float>* selection, std::atomic<float>* gain, std::atomic<float>* wet) {
        odTypeParam = *selection;
        odGain = juce::Decibels::decibelsToGain<float>(*gain);
        odWet = *wet / 100.;
    }

    double setOD() {
        switch (odTypeParam) {
        case 0:
            if (filterBypass)
                return od.overdrive(setFilter(), odGain, odWet);
            else
                return od.overdrive(setEnvelope(), odGain, odWet);

        case 1:
            if (filterBypass)
                return od.distortion(setFilter(), odGain, odWet);
            else
                return od.distortion(setEnvelope(), odGain, odWet);

        default:
            if (filterBypass)
                return od.overdrive(setFilter(), odGain, odWet);
            else
                return od.overdrive(setEnvelope(), odGain, odWet);
        }
        
    }

    // ===========================================

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    // ===========================================
    void stopNote(float velocity, bool allowTailOff) {
        env1.trigger = 0;
        allowTailOff = true;
        if (velocity == 0) {
            SynthesiserVoice::clearCurrentNote();
        }
    }
    // ============================================
    void pitchWheelMoved(int newPitchWheelValue) {

    }
    // =============================================
    void controllerMoved(int controllerNumber, int newControllerValue) {

    }
    // ===========================================
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override {
        for (int sample = 0; sample < numSamples; ++sample) {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
                outputBuffer.addSample(channel, startSample, setOD() * juce::Decibels::decibelsToGain<float>(masterGain));
            }
            ++startSample;
        }
    }
private:
    // Oscillator
    double frequency, level;        
    double sample1, sample2;        
    int osc1Wave, osc2Wave;         
    double osc1level, osc2level;    
    int octIdx;                     
    float octShiftFreq[5] = { 0.25, 0.5, 1, 2, 4 }; // These are the values used to change OSC2 frequency in setOscType()

    // Filter
    int filterTypeParam;                
    float cutoffParam, resonanceParam;  
    bool filterBypass;                  

    // Overdrive
    float odGain, odWet;
    int odTypeParam;

    float masterGain;

    myOsc osc1, osc2;
    myEnvelope env1;
    myFilter filter;
    myODfx od;

};