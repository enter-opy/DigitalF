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
    setSize (1000, 300);

    bitdepthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, BITDEPTH_ID, bitdepthSlider);
    samplerateValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, SAMPLERATE_ID, samplerateSlider);
    clipCeilingValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, CLIPCELING_ID, clipCeilingSlider);
    crackleValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, CRACKLE_ID, crackleSlider);
    gainValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, GAIN_ID, gainSlider);

    bitdepthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    bitdepthSlider.setRange(2.0, 32.0, 1.0);
    bitdepthSlider.setSkewFactorFromMidPoint(8.0);
    bitdepthSlider.setValue(32.0);
    bitdepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    bitdepthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&bitdepthSlider);

    samplerateSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    samplerateSlider.setRange(2.0, 44100.0, 1.0);
    samplerateSlider.setValue(44100.0);
    samplerateSlider.setTextValueSuffix(" Hz");
    samplerateSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    samplerateSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&samplerateSlider);

    clipCeilingSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    clipCeilingSlider.setRange(-48.0, 0.0, 0.1);
    clipCeilingSlider.setValue(0.0);
    gainSlider.setSkewFactorFromMidPoint(-12.0f);
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

    gainSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    gainSlider.setRange(-48.0, 48.0, 0.1);
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
    bitdepthSlider.setBounds(40, 100, 100, 100);
    samplerateSlider.setBounds(200, 100, 100, 100);
    clipCeilingSlider.setBounds(360, 100, 100, 100);
    crackleSlider.setBounds(520, 100, 100, 100);
    gainSlider.setBounds(780, 100, 100, 100);
}
