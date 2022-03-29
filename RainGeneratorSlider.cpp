//
// Created by edgallyot on 18/02/2022.
//

#include "RainGeneratorSlider.h"

#include <memory>


RainGeneratorSlider::RainGeneratorSlider (juce::AudioProcessorValueTreeState& treeState, std::string ID,
                                          std::string Name) :
        parameters (treeState),
        ID (ID),
        Name (Name)
{
    // Slider Style
    m_slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    m_slider.getLookAndFeel ().setColour (juce::Slider::thumbColourId, juce::Colours::deeppink);
    m_slider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    //DBG(parameters.getRawParameterValue (this->ID)->load() );

    // Setting Default Slider Values
    m_labelValue.setText (std::to_string (parameters.getRawParameterValue (this->ID)->load ()),
                          juce::dontSendNotification);
    m_labelName.setText (Name, juce::dontSendNotification);
    m_slider.addListener (this);


    // Making visible and attatching state to GUI
    m_slider.addListener (this);
    addAndMakeVisible (m_slider);
    addAndMakeVisible (m_labelValue);
    addAndMakeVisible (m_labelName);

    attachment = std::make_unique<SliderAttachment> (treeState, ID, m_slider);
}

void RainGeneratorSlider::resized ()
{
    auto sliderArea = getLocalBounds ();
    auto labelPosition = 10;
    auto labelHeight = 0;
    sliderArea.removeFromTop (labelPosition + labelHeight);
    sliderArea.removeFromBottom (labelPosition + labelHeight);

    auto labelValueArea = getLocalBounds ();
    auto labelNameArea = getLocalBounds ();
    labelValueArea.removeFromTop (sliderArea.getHeight () - labelPosition - (labelHeight / 2));
    labelValueArea.removeFromBottom (labelPosition + (labelHeight / 2));
    labelNameArea.removeFromBottom (sliderArea.getHeight () - labelPosition - (labelHeight / 2));
    labelNameArea.removeFromTop (labelPosition + (labelHeight / 2));

    m_slider.setBounds (sliderArea);
    m_labelValue.setBounds (labelValueArea);
    m_labelValue.setJustificationType (juce::Justification::centred);
    m_labelName.setBounds (labelNameArea);
    m_labelName.setJustificationType (juce::Justification::centred);
}
void RainGeneratorSlider::sliderValueChanged (juce::Slider* slider)
{
    m_labelValue.setText (std::to_string (parameters.getRawParameterValue (ID)->load ()), juce::dontSendNotification);
}

void RainGeneratorSlider::setSkewForTone ()
{
    m_slider.setRange(VTS_MIN_BUBBLE_TONE, VTS_MAX_BUBBLE_TONE, 0.0001f);
    m_slider.setSkewFactorFromMidPoint (2000.0f);
}
