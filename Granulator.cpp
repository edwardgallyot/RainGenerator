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
    highPassModule.prepare (sampleRate, samplesPerBlock, 2);
    lowPassModule.prepare (sampleRate, samplesPerBlock, 2);
}


void Granulator::process (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi,
                          std::vector<std::atomic<float>*>& parameters)
{
//    DBG(cosTable.get_sample (m_parameters[RainParameters::Noise_Volume]->load () * phasor.getMaxIndex () * 2.0f));

    juce::ignoreUnused (midi);
//    DBG(totalNumOutputChannels);
    auto ms = Fs / 1000.0f;

    juce::AudioBuffer<float> dropBuffer {buffer.getNumChannels (), buffer.getNumSamples ()};
    juce::AudioBuffer<float> bubbleBuffer {buffer.getNumChannels (), buffer.getNumSamples ()};
    juce::AudioBuffer<float> noiseBuffer {buffer.getNumChannels (), buffer.getNumSamples ()};

    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {
        auto randint = noise.get_sample (static_cast<float>(noise_index));
        auto density = 1.6f - m_smoothedParameters[RainParameters::Drop_Density].getNextValue ();
        auto duration = Fs / (80 + (std::abs (randint)) * 80);
        auto amp = 0.5f - (std::abs (randint) * 0.25f);
        auto speed = 20.0f + (m_smoothedParameters[RainParameters::Drop_Pitch].getNextValue () * 40.0f) / 2.0f;
        auto spread = m_smoothedParameters[RainParameters::Spread].getNextValue ();
        float pan = static_cast<float>(rand () % 100) - 50.0f;
        pan = 0.5 + (spread * static_cast<float>(pan / 100.0f));


        if (randint > density)
        {
            for (size_t i = 0; i < num_of_drops; ++i)
            {
                auto* grain = &(drops[i]);
                if (!grain->isActive ())
                {
                    grain->activateGrain (duration, speed, amp, pan, &cosTable, &parabolicEnvelope);
                    break;
                }
            }
        }

        density = 1.6f - m_smoothedParameters[RainParameters::Bubble_Density].getNextValue ();
        speed = 20.0f + (m_smoothedParameters[RainParameters::Bubble_Pitch].getNextValue () * 40.0f) / 2.0f;

        if (randint > density)
        {
            for (size_t i = 0; i < num_of_bubbles; ++i)
            {
                auto* grain = &(bubbles[i]);
                if (!grain->isActive ())
                {
                    grain->activateGrain (duration, speed, amp, pan, &cosTable, &guassianEnvelope);
                    break;
                }
            }
        }

        // Set the bubble grain Parameters

        float dropOutput[2] {0.0f, 0.0f};

        for (size_t i = 0; i < num_of_drops; ++i)
        {
            auto* grain = &(drops[i]);
            if (grain->isActive ())
            {
                grain->getNextSample (dropOutput);
            }
        }

        auto dropVolume = m_smoothedParameters[RainParameters::Drop_Volume].getNextValue ();

        for (size_t i = 0; i < 2; ++i)
            dropOutput[i] *= dropVolume;


        float bubbleOutput[2] {0.0f, 0.0f};
//
        for (size_t i = 0; i < num_of_bubbles; ++i)
        {
            auto* grain = &(bubbles[i]);
            if (grain->isActive ())
                grain->getNextSample (bubbleOutput);
        }
        auto bubbleVolume = m_smoothedParameters[RainParameters::Bubble_Volume].getNextValue ();

        for (size_t i = 0; i < 2; ++i)
            bubbleOutput[i] *= bubbleVolume;


        float noiseOutput[2] {0.0f, 0.0f};

        auto noiseVolume = m_smoothedParameters[RainParameters::Noise_Volume].getNextValue ();

        for (size_t i = 0; i < 2; ++i)
        {
            noiseOutput[i] = random.nextFloat () * 0.1f;
            noiseOutput[i] *= noiseVolume;
        }
        noiseOutput[0] *= (1.0f - pan);
        noiseOutput[1] *= pan;


        for (int channel = 0; channel < 2; ++channel)
        {
            bubbleBuffer.setSample (channel, sample, bubbleOutput[channel]);
            dropBuffer.setSample (channel, sample, dropOutput[channel]);
            noiseBuffer.setSample (channel, sample, noiseOutput[channel]);
        }

        noise_index += 0.01f;

        if (noise_index == static_cast<float>(noise.getSize ()))
            noise_index = 0.0f;
    }

    // Perform Tone Operations and Sum buffers

    auto bubbleTone = parameters[RainParameters::Bubble_Tone]->load ();
    auto dropTone = parameters[RainParameters::Drop_Tone]->load ();
    auto noiseTone = parameters[RainParameters::Noise_Tone]->load ();

    highPassModule.process (bubbleBuffer, midi, bubbleTone);
    highPassModule.process (dropBuffer, midi, dropTone);
    lowPassModule.process (noiseBuffer, midi, noiseTone);

    // Summing the buffers
    for (auto sample = 0; sample < buffer.getNumSamples (); ++sample)
    {
        for (int channel = 0; channel < 2; ++channel)
        {
            auto* write = buffer.getWritePointer (channel, sample);
            *write += bubbleBuffer.getSample (channel, sample);
            *write += dropBuffer.getSample (channel, sample);
            *write += noiseBuffer.getSample (channel, sample);
        }
    }
}

void Granulator::setParameters (std::vector<std::atomic<float>*>& parameters)
{
    for (int i = 0; i < VTS_PARAMS_N; ++i)
    {
        m_smoothedParameters[i].setTargetValue (parameters[i]->load ());
    }
}
