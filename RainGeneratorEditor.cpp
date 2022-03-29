#include "RainGeneratorProcessor.h"
#include "RainGeneratorEditor.h"
#include "id_name_vts.h"

//==============================================================================
RainGeneratorEditor::RainGeneratorEditor (RainGeneratorProcessor& p, juce::AudioProcessorValueTreeState& vts) :
        AudioProcessorEditor (&p),
        processorRef (p),
        sliderBank1 (p, vts, {VTS_ID_NOISE_TONE, VTS_NAME_NOISE_TONE}, {VTS_ID_NOISE_VOL, VTS_NAME_NOISE_VOL}),
        sliderBank2 (p, vts, {VTS_ID_BUBBLE_DENSITY, VTS_NAME_BUBBLE_DENSITY},
                     {VTS_ID_BUBBLE_PITCH, VTS_NAME_BUBBLE_PITCH}),
        sliderBank3 (p, vts, {VTS_ID_BUBBLE_TONE, VTS_NAME_BUBBLE_TONE},
                     {VTS_ID_BUBBLE_VOLUME, VTS_NAME_BUBBLE_VOLUME}),
        sliderBank4 (p, vts, {VTS_ID_DROP_DENSITY, VTS_NAME_DROP_DENSITY}, {VTS_ID_DROP_PITCH, VTS_NAME_DROP_PITCH}),
        sliderBank5 (p, vts, {VTS_ID_DROP_TONE, VTS_NAME_DROP_TONE}, {VTS_ID_DROP_VOLUME, VTS_NAME_DROP_VOLUME}),
        sliderBank6 (p, vts, {VTS_ID_VOLUME, VTS_NAME_VOLUME}, {VTS_ID_SPREAD, VTS_NAME_SPREAD})
{
    juce::ignoreUnused (processorRef);
    addAndMakeVisible (sliderBank1);
    addAndMakeVisible (sliderBank2);
    addAndMakeVisible (sliderBank3);
    addAndMakeVisible (sliderBank4);
    addAndMakeVisible (sliderBank5);
    addAndMakeVisible (sliderBank6);
    sliderBank1.setTopSliderTone();
    sliderBank3.setTopSliderTone();
    sliderBank5.setTopSliderTone();
// Make sure that before the constructor has finished, you've set the
// editor's size to whatever you need it to be.
    setSize (700, 400);
}

RainGeneratorEditor::~RainGeneratorEditor ()
{
}

//==============================================================================
void RainGeneratorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::blueviolet);

}

void RainGeneratorEditor::resized ()
{
    sliderBank1.setTopSliderTone();
    sliderBank3.setTopSliderTone();
    sliderBank5.setTopSliderTone();

    std::vector<juce::Rectangle<int>> areas {6, getLocalBounds ()};

    auto padding = 10;

    for (int i = 0; i < areas.size (); ++i)
    {
        areas[i].removeFromRight ((getWidth () / 6) * (5 - i));
        areas[i].removeFromLeft ((getWidth () / 6) * (i));
        areas[i].removeFromTop (padding);
        areas[i].removeFromBottom (padding);
    }

    sliderBank1.setBounds (areas[0]);
    sliderBank2.setBounds (areas[1]);
    sliderBank3.setBounds (areas[2]);
    sliderBank4.setBounds (areas[3]);
    sliderBank5.setBounds (areas[4]);
    sliderBank6.setBounds (areas[5]);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

