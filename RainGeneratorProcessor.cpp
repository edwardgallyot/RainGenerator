#include "RainGeneratorProcessor.h"
#include "RainGeneratorEditor.h"
#include "id_name_vts.h"

//==============================================================================
RainGeneratorProcessor::RainGeneratorProcessor ()
        : AudioProcessor (BusesProperties ()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                                  .withInput ("Input", juce::AudioChannelSet::stereo (), true)
#endif
                                  .withOutput ("Output", juce::AudioChannelSet::stereo (), true)
#endif
),
          parameters (*this, nullptr, juce::Identifier (VTS_ID_TREE),
                      createParameterLayout ()
          )
{
}

RainGeneratorProcessor::~RainGeneratorProcessor ()
{
    size_t i = 0;
    for (const auto& id: m_ids)
    {
        m_parameters[i] = parameters.getRawParameterValue (id);
        i++;
    }
}

//==============================================================================
void RainGeneratorProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
    granulator.prepare (sampleRate, samplesPerBlock);
    gainModule.prepare(sampleRate, samplesPerBlock);
}

void RainGeneratorProcessor::releaseResources ()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void RainGeneratorProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                           juce::MidiBuffer& midiMessages)
{
    size_t i = 0;
    for (const auto& id: m_ids)
    {
        m_parameters[i] = parameters.getRawParameterValue (id);
        i++;
    }

//    DBG(m_parameters[RainParameters::Drop_Density]->load());

    granulator.setParameters (m_parameters);
//    DBG(cosTable.get_sample (m_parameters[RainParameters::Noise_Volume]->load () * phasor.getMaxIndex () * 2.0f));

    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels ();
    auto totalNumOutputChannels = getTotalNumOutputChannels ();

//    DBG(totalNumOutputChannels);


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples ());

    granulator.process (buffer, midiMessages, m_parameters);

    auto gain = m_parameters[RainParameters::Volume]->load();
    gainModule.process(buffer, midiMessages, gain);

}

juce::AudioProcessorEditor* RainGeneratorProcessor::createEditor ()
{
    return new RainGeneratorEditor (*this, parameters);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new RainGeneratorProcessor ();
}

juce::AudioProcessorValueTreeState::ParameterLayout RainGeneratorProcessor::createParameterLayout ()
{
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    DBG(m_ids.size ());

    for (size_t i = 0; i < m_ids.size (); ++i)
    {
        params.add (std::make_unique<juce::AudioParameterFloat> (m_ids[i],
                                                                 m_names[i],
                                                                 m_minimums[i],
                                                                 m_maxes[i],
                                                                 m_defaults[i]));
    }
    return params;
}

void RainGeneratorProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState ();
    std::unique_ptr<juce::XmlElement> xml (state.createXml ());
    copyXmlToBinary (*xml, destData);
}
void RainGeneratorProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get () != nullptr)
        if (xmlState->hasTagName (parameters.state.getType ()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}


