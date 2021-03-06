//
// Created by edgallyot on 23/03/2022.
//

#include "ParabolicRainGrain.h"

ParabolicRainGrain::ParabolicRainGrain (Grain* grain, Envelope* envelope, Phasor* phasor) : GrainGenerator (grain, envelope, phasor)
{
}
void ParabolicRainGrain::getNextSample (float output[])
{
    auto phase = phasor->get_sample (phasor_index);
    auto out = envelope->get_sample (phase * envelope->getSize()) * amp;

    phasor_index += phasor_delta * speed;


    if (phasor_index >= static_cast<float>(phasor->getSize ()))
    {
        phasor_index = 0.0f;
        active = false;
        out = 0.0f;
    }

    output[0] += (1.0f - pan) * out;
    output[1] += pan * out;
}
