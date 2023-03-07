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
class DigitalFAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DigitalFAudioProcessorEditor (DigitalFAudioProcessor&);
    ~DigitalFAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    DigitalFAudioProcessor& audioProcessor;

    Slider bitdepthSlider;
    Slider samplerateSlider;
    Slider clipCeilingSlider;
    Slider crackleSlider;
    Slider noiseLevelSlider;
    Slider gainSlider;

public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> bitdepthValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> samplerateValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> clipCeilingValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> crackleValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> noiseLevelValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> gainValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DigitalFAudioProcessorEditor)
};
