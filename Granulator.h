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

class Granulator
{
public:
    Granulator ();
    void prepare (double sampleRate, double samplesPerBlock);
    void setParameters (std::vector<std::atomic<float>*>& m_parameters);
    void process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi);
private:
    Phasor phasor {10000};
    Noise noise {10000};
    CosTable cosTable {10000};

    Envelopes parabolic = Envelopes::Parabolic;
    Envelopes guassian = Envelopes::Guassian;
    Envelopes exponential = Envelopes::Exponential;

    Envelope parabolicEnvelope {10000, &parabolic};
    Envelope exponentialEnvelope {10000, &exponential};
    Envelope guassianEnvelope {10000, &guassian};


    ParabolicRainGrain parabolicRainGrain {cosTable, parabolicEnvelope, phasor};
    std::vector<ParabolicRainGrain> parabolicGrains {100, parabolicRainGrain};

    BubbleGrain bubbleGrain{cosTable, guassianEnvelope, phasor, exponentialEnvelope, cosTable};

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
    double Fs{0.0f};

};


#endif //RAINGENERATOR_GRANULATOR_H
