/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LittleBitAudioProcessorEditor::LittleBitAudioProcessorEditor (LittleBitAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    bitdepthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, BITDEPTH_ID, bitdepthSlider);
    bitdepthValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, BITDEPTH_ID, bitdepthSlider);

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
}

LittleBitAudioProcessorEditor::~LittleBitAudioProcessorEditor()
{
}

//==============================================================================
void LittleBitAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void LittleBitAudioProcessorEditor::resized()
{
    bitdepthSlider.setBounds(40, 100, 100, 100);
    samplerateSlider.setBounds(200, 100, 100, 100);
}
