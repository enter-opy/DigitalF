/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define BITDEPTH_ID "bitdepth"
#define BITDEPTH_NAME "Bitdepth"

#define SAMPLERATE_ID "samplerate"
#define SAMPLERATE_NAME "Samplerate"

#define JITTER_ID "jitter"
#define JITTER_NAME "Jitter"

#define CLIPCELING_ID "clipceiling"
#define CLIPCELING_NAME "Clipceiling"

#define CRACKLE_ID "crackle"
#define CRACKLE_NAME "Crackle"

#define MIX_ID "mix"
#define MIX_NAME "Mix"

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"

#define MONO_ID "mono"
#define MONO_NAME "Mono"

//==============================================================================
/**
*/
class DigitalFAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    DigitalFAudioProcessor();
    ~DigitalFAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    AudioProcessorValueTreeState treeState;
private:
    float drySampleValue;
    float wetSampleValue;
    float leftSampleValue;
    float rightSampleValue;

    float sr;

    Random random;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DigitalFAudioProcessor)
};
