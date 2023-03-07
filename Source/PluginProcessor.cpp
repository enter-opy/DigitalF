/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DigitalFAudioProcessor::DigitalFAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    treeState(*this, nullptr, "PARAMETER",
        {
            std::make_unique<AudioParameterFloat>(BITDEPTH_ID, BITDEPTH_NAME, 2.0f, 32.0f, 32.0f),
            std::make_unique<AudioParameterFloat>(SAMPLERATE_ID, SAMPLERATE_NAME, 0.0f, 44100.0f, 44100.0f),
            std::make_unique<AudioParameterFloat>(CLIPCELING_ID, CLIPCELING_NAME, -48.0f, 0.0f, 0.0f),
            std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, -48.0f, 48.0f, 0.0f)
        }
    )
#endif
{
    treeState.state = ValueTree("savedParams");
}

DigitalFAudioProcessor::~DigitalFAudioProcessor()
{
}

//==============================================================================
const juce::String DigitalFAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DigitalFAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DigitalFAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DigitalFAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DigitalFAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DigitalFAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DigitalFAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DigitalFAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DigitalFAudioProcessor::getProgramName (int index)
{
    return {};
}

void DigitalFAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DigitalFAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DigitalFAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DigitalFAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DigitalFAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    int maxBitdepthValue = pow(2, *treeState.getRawParameterValue(BITDEPTH_ID)) / 2;
    float clipCeiling = Decibels::decibelsToGain((float)*treeState.getRawParameterValue(CLIPCELING_ID));
    float gain = Decibels::decibelsToGain((float)*treeState.getRawParameterValue(GAIN_ID));

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            currentSampleValue = buffer.getSample(channel, sample);

            newSampleValue = round((currentSampleValue)*maxBitdepthValue) / maxBitdepthValue;

            if (newSampleValue >= clipCeiling) {
                newSampleValue = clipCeiling;
            }
            else if (newSampleValue <= -clipCeiling) {
                newSampleValue = -clipCeiling;
            }

            newSampleValue *= gain;

            channelData[sample] = newSampleValue;
        }
    }
}

//==============================================================================
bool DigitalFAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DigitalFAudioProcessor::createEditor()
{
    return new DigitalFAudioProcessorEditor (*this);
}

//==============================================================================
void DigitalFAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr <XmlElement> xml(treeState.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void DigitalFAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr <XmlElement> params(getXmlFromBinary(data, sizeInBytes));

    if (params != nullptr) {
        if (params->hasTagName(treeState.state.getType())) {
            treeState.state = ValueTree::fromXml(*params);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DigitalFAudioProcessor();
}
