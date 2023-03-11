/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DigitalFAudioProcessorEditor::DigitalFAudioProcessorEditor (DigitalFAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (1000, 600);

    bitdepthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, BITDEPTH_ID, bitdepthSlider);
    samplerateValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, SAMPLERATE_ID, samplerateSlider);
    jitterValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, JITTER_ID, jitterSlider);
    clipCeilingValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, CLIPCELING_ID, clipCeilingSlider);
    crackleValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, CRACKLE_ID, crackleSlider);
    noiseLevelValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, NOISELEVEL_ID, noiseLevelSlider);
    mixValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, MIX_ID, mixSlider);
    gainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, GAIN_ID, gainSlider);

    bitdepthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    bitdepthSlider.setRange(2.0, 32.0, 1.0);
    bitdepthSlider.setSkewFactorFromMidPoint(8.0);
    bitdepthSlider.setValue(32.0);
    bitdepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    bitdepthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&bitdepthSlider);

    samplerateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    samplerateSlider.setRange(44.0, 44100.0, 1.0);
    samplerateSlider.setValue(44100.0);
    samplerateSlider.setTextValueSuffix(" Hz");
    samplerateSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    samplerateSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&samplerateSlider);

    jitterSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    jitterSlider.setRange(0.0, 100.0, 1.0);
    jitterSlider.setValue(0.0);
    jitterSlider.setTextValueSuffix(" %");
    jitterSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    jitterSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&jitterSlider);

    clipCeilingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    clipCeilingSlider.setRange(-24.0, 0.0, 0.1);
    clipCeilingSlider.setValue(0.0);
    clipCeilingSlider.setTextValueSuffix(" dB");
    clipCeilingSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    clipCeilingSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&clipCeilingSlider);

    crackleSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    crackleSlider.setRange(0.0, 100.0, 1.0);
    crackleSlider.setValue(0.0);
    crackleSlider.setTextValueSuffix(" %");
    crackleSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    crackleSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&crackleSlider);

    noiseLevelSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    noiseLevelSlider.setRange(0.0, 100.0, 1.0);
    noiseLevelSlider.setValue(0.0);
    noiseLevelSlider.setTextValueSuffix(" %");
    noiseLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    noiseLevelSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&noiseLevelSlider);

    mixSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    mixSlider.setRange(0.0, 100.0, 1.0);
    mixSlider.setValue(100.0);
    mixSlider.setTextValueSuffix(" %");
    mixSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    mixSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&mixSlider);

    gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    gainSlider.setRange(-24.0, 24.0, 0.1);
    gainSlider.setValue(0.0);
    gainSlider.setSkewFactorFromMidPoint(0.0f);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    gainSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&gainSlider);
}

DigitalFAudioProcessorEditor::~DigitalFAudioProcessorEditor()
{
}

//==============================================================================
void DigitalFAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void DigitalFAudioProcessorEditor::resized()
{
    // Artifacts
    bitdepthSlider.setBounds(100, 100, 100, 100);
    samplerateSlider.setBounds(220, 100, 100, 100);
    jitterSlider.setBounds(340, 100, 100, 100);
    clipCeilingSlider.setBounds(460, 100, 100, 100);
    crackleSlider.setBounds(580, 100, 100, 100);
    
    // Noise
    noiseLevelSlider.setBounds(290, 310, 200, 200);

    // Output
    mixSlider.setBounds(830, 300, 100, 100);
    gainSlider.setBounds(830, 420, 100, 100);
}
