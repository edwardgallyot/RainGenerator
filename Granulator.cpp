//
// Created by edgallyot on 22/03/2022.
//

#include "Granulator.h"

Granulator::Granulator ()
{
}

void Granulator::prepare (double sampleRate, double samplesPerBlock)
{
    for (int i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].reset (sampleRate, 0.05f);
    }
    Fs = sampleRate;
}


void Granulator::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
//    DBG(cosTable.get_sample (m_parameters[RainParameters::Noise_Volume]->load () * phasor.getMaxIndex () * 2.0f));

    juce::ignoreUnused (midi);
//    DBG(totalNumOutputChannels);
    auto ms = Fs / 1000.0f;

    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {
        auto randint = noise.get_sample (static_cast<float>(noise_index));
        auto density = 1.6f - m_smoothedParameters[RainParameters::Drop_Density].getNextValue ();
        auto duration = Fs / (40 + (std::abs(randint) * 0.5) * 40);
        auto amp = 0.5f - (std::abs(randint) * 0.25f);
        amp *= m_smoothedParameters[RainParameters::Drop_Volume].getNextValue();
        auto speed = 1.0f + (m_smoothedParameters[RainParameters::Drop_Pitch].getNextValue () * 10.0f) / 4.0f;
        auto spread = m_smoothedParameters[RainParameters::Spread].getNextValue();
        float pan = static_cast<float>(rand() % 100) - 50.0f;
        pan = 0.5 + (spread * static_cast<float>(pan / 100.0f));

        if (randint > density)
        {
            for (auto& grain: parabolicGrains)
            {
                if (!grain.isActive ())
                {
                    parabolicRainGrain.activateGrain (duration, speed, amp, pan, noise, parabolicEnvelope);
                    break;
                }
            }
        }

        // Set the bubble grain Parameters

        float output[2] {0.0f, 0.0f};

        for (auto& grain: parabolicGrains)
        {
            if (parabolicRainGrain.isActive ())
                parabolicRainGrain.getNextSample (output);
        }

        for (int channel = 0; channel < 2; ++channel)
        {
            buffer.setSample (channel, sample, output[channel]);
        }

        noise_index += 0.01f;

        if (noise_index == static_cast<float>(noise.getSize ()))
            noise_index = 0.0f;
    }
}

void Granulator::setParameters (std::vector<std::atomic<float>*>& parameters)
{
    for (int i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].setTargetValue (parameters[i]->load ());
    }
}
