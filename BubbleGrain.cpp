//
// Created by edgallyot on 23/03/2022.
//

#include "BubbleGrain.h"

BubbleGrain::BubbleGrain (Grain& grain, Envelope& envelope, Phasor& phasor, Envelope& pitchEnvelope)
        : GrainGenerator (grain, envelope, phasor),
          pitchEnvelope (pitchEnvelope),
          grain(grain)
{
}
void BubbleGrain::getNextSample (float* output)
{
    // TODO Complete the DSP 4 Bubbles
    auto phase = phasor.get_sample (phasor_index);
    auto pitch = pitchEnvelope.get_sample(phase * pitchEnvelope.getSize());
    //DBG(pitch);
    auto out = grain.get_sample (phase * grain.getSize () * (pitch * 30));
    auto grainAmp = amp;
//    out *= envelope.get_sample (phase * envelope.getSize());
//    auto pitch = pitchEnvelope.get_sample (phase * static_cast<float>(pitchEnvelope.getSize ())) * 3000;
//    auto out = grain.get_sample (phase * pitch);
//
    if (phasor_index <= ampTrigger)
    {
        grainAmp *= 0.0f;
    } else
    {
        phase = phasor.get_sample (ampIndex);
        grainAmp *= envelope.get_sample (phase * envelope.getSize ());
        ampIndex += ampDelta;

    }
    phasor_index += phasor_delta * speed;
//
    if (phasor_index >= static_cast<float>(phasor.getSize ()))
    {
        phasor_index = 0.0f;
        ampIndex = 0.0f;
        out = 0.0f;
        active = false;
    }
    out *= grainAmp;

    output[0] += (1.0f - pan) * out;
    output[1] += pan * out;
}
void BubbleGrain::activateGrain (float duration, float speed, float amp, float pan, Grain& p_grain, Envelope& p_envelope)
{
    // TODO Override the base classes activate grain function
    GrainGenerator::activateGrain (duration, speed, amp, pan, p_grain, p_envelope);
    this->envelope = p_envelope;
    this->grain = p_grain;
    this->speed = speed;
    this->amp = amp;
    this->duration = duration * 150;
    this->pan = pan;
    offset = duration;
    phasor_delta = static_cast<float>( phasor.getSize ()) / this->duration;
    ampDelta = static_cast<float>( phasor.getSize ()) / (this->duration - offset);
    ampTrigger = offset * phasor_delta;
    this->active = true;
}
