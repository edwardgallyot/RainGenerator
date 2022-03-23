#pragma once

#include "RainGeneratorProcessor.h"
#include "SliderBank.h"

//==============================================================================
class RainGeneratorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit RainGeneratorEditor (RainGeneratorProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~RainGeneratorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;

    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RainGeneratorProcessor& processorRef;

    SliderBank sliderBank1;
    SliderBank sliderBank2;
    SliderBank sliderBank3;
    SliderBank sliderBank4;
    SliderBank sliderBank5;
    SliderBank sliderBank6;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RainGeneratorEditor)
};

