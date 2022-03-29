#pragma once

#include <JuceHeader.h>
#include "BaseProcessor.h"
#include "id_name_vts.h"
#include "GrainGenerator.h"
#include "Noise.h"
#include "Envelope.h"
#include "CosTable.h"
#include "ParabolicRainGrain.h"
#include "Granulator.h"
#include "GainModule.h"

//==============================================================================
class RainGeneratorProcessor : public BaseProcessor
{
public:
    //==============================================================================
    RainGeneratorProcessor ();
    ~RainGeneratorProcessor () override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources () override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor () override;

private:

    std::vector<juce::String> m_ids {VTS_ID_NOISE_TONE, VTS_ID_NOISE_VOL, VTS_ID_BUBBLE_DENSITY,
                                     VTS_ID_BUBBLE_PITCH, VTS_ID_BUBBLE_TONE, VTS_ID_BUBBLE_VOLUME,
                                     VTS_ID_DROP_DENSITY, VTS_ID_DROP_PITCH, VTS_ID_DROP_TONE,
                                     VTS_ID_DROP_VOLUME, VTS_ID_VOLUME, VTS_ID_SPREAD};

    std::vector<juce::String> m_names {VTS_NAME_NOISE_TONE, VTS_NAME_NOISE_VOL, VTS_NAME_BUBBLE_DENSITY,
                                       VTS_NAME_BUBBLE_PITCH, VTS_NAME_BUBBLE_TONE, VTS_NAME_BUBBLE_VOLUME,
                                       VTS_NAME_DROP_DENSITY, VTS_NAME_DROP_PITCH, VTS_NAME_DROP_TONE,
                                       VTS_NAME_DROP_VOLUME, VTS_NAME_VOLUME, VTS_NAME_SPREAD};

    std::vector<float> m_minimums {VTS_MIN_NOISE_TONE, VTS_MIN_NOISE_VOL, VTS_MIN_BUBBLE_DENSITY,
                                   VTS_MIN_BUBBLE_PITCH, VTS_MIN_BUBBLE_TONE, VTS_MIN_BUBBLE_VOLUME,
                                   VTS_MIN_DROP_DENSITY, VTS_MIN_DROP_PITCH, VTS_MIN_DROP_TONE,
                                   VTS_MIN_DROP_VOLUME, VTS_MIN_VOLUME, VTS_MIN_SPREAD};

    std::vector<float> m_maxes {VTS_MAX_NOISE_TONE, VTS_MAX_NOISE_VOL, VTS_MAX_BUBBLE_DENSITY,
                                VTS_MAX_BUBBLE_PITCH, VTS_MAX_BUBBLE_TONE, VTS_MAX_BUBBLE_VOLUME,
                                VTS_MAX_DROP_DENSITY, VTS_MAX_DROP_PITCH, VTS_MAX_DROP_TONE,
                                VTS_MAX_DROP_VOLUME, VTS_MAX_VOLUME, VTS_MAX_SPREAD};

    std::vector<float> m_defaults {VTS_DEFAULT_NOISE_TONE, VTS_DEFAULT_NOISE_VOL, VTS_DEFAULT_BUBBLE_DENSITY,
                                   VTS_DEFAULT_BUBBLE_PITCH, VTS_DEFAULT_BUBBLE_TONE, VTS_DEFAULT_BUBBLE_VOLUME,
                                   VTS_DEFAULT_DROP_DENSITY, VTS_DEFAULT_DROP_PITCH, VTS_DEFAULT_DROP_TONE,
                                   VTS_DEFAULT_DROP_VOLUME, VTS_DEFAULT_VOLUME, VTS_DEFAULT_SPREAD};

    std::vector<std::atomic<float>*> m_parameters {12, nullptr};

    juce::AudioProcessorValueTreeState parameters;
    Granulator granulator{};
    GainModule gainModule;
    // Vectors for Ids Go Here
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout ();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RainGeneratorProcessor)
};

