//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_GRANULATOR_H
#define RAINGENERATOR_GRANULATOR_H


#include "Phasor.h"
#include "Noise.h"
#include "id_name_vts.h"
#include "Envelope.h"
#include "CosTable.h"
#include "ParabolicRainGrain.h"
#include "BubbleGrain.h"
#include "id_name_vts.h"
#include "LowPassModule.h"
#include "HighPassModule.h"

class Granulator
{
public:
    Granulator ();
    void prepare (double sampleRate, double samplesPerBlock);
    void setParameters (std::vector<std::atomic<float>*>& m_parameters);
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi,
                  std::vector<std::atomic<float>*>& parameters);
private:
    Phasor phasor {100000};
    Noise noise {10000};
    CosTable cosTable {100000};

    Envelopes parabolic = Envelopes::Parabolic;
    Envelopes guassian = Envelopes::Guassian;
    Envelopes exponential = Envelopes::Exponential;

    Envelope parabolicEnvelope {100000, &parabolic};
    Envelope exponentialEnvelope {100000, &exponential};
    Envelope guassianEnvelope {100000, &guassian};

    size_t num_of_drops {5};
    ParabolicRainGrain drops[5] = {{&cosTable, &parabolicEnvelope, &phasor},
                                   {&cosTable, &parabolicEnvelope, &phasor},
                                   {&cosTable, &parabolicEnvelope, &phasor},
                                   {&cosTable, &parabolicEnvelope, &phasor},
                                   {&cosTable, &parabolicEnvelope, &phasor}
    };


    size_t num_of_bubbles {5};
    BubbleGrain bubbles[5] = {{&cosTable, &guassianEnvelope, &phasor, &exponentialEnvelope},
                              {&cosTable, &guassianEnvelope, &phasor, &exponentialEnvelope},
                              {&cosTable, &guassianEnvelope, &phasor, &exponentialEnvelope},
                              {&cosTable, &guassianEnvelope, &phasor, &exponentialEnvelope},
                              {&cosTable, &guassianEnvelope, &phasor, &exponentialEnvelope}
    };

    juce::LinearSmoothedValue<float> m_smoothedParameters[VTS_PARAMS_N] {{0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f},
                                                                         {0.0f}};

    float noise_index {0.0f};
    double Fs {0.0f};
    juce::Random random;

    LowPassModule lowPassModule;
    HighPassModule highPassModule;

};


#endif //RAINGENERATOR_GRANULATOR_H
