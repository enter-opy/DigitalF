/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LittleBitAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LittleBitAudioProcessorEditor (LittleBitAudioProcessor&);
    ~LittleBitAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LittleBitAudioProcessor& audioProcessor;

    Slider bitdepthSlider;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bitdepthValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LittleBitAudioProcessorEditor)
};
