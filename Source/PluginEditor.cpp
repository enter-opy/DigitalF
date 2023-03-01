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

    bitdepthSlider.setSliderStyle(Slider::RotaryVerticalDrag);
    bitdepthSlider.setRange(2, 32);
    bitdepthSlider.setValue(32);
    bitdepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    bitdepthSlider.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&bitdepthSlider);
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
}
