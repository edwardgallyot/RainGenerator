//
// Created by edgallyot on 23/03/2022.
//

#include "BubbleGrain.h"

BubbleGrain::BubbleGrain (Grain& grain,
                          Envelope& envelope,
                          Phasor& phasor,
                          Envelope& pitchEnvelope,
                          CosTable& cosTable)
        : GrainGenerator (grain, envelope, phasor),
          cosTable (cosTable),
          pitchEnvelope (pitchEnvelope)
{
}
void BubbleGrain::getNextSample (float* output)
{
    // TODO Complete the DSP for Bubbles
    auto phase = phasor.get_sample (phasor_index) * amp;
    auto out = envelope.get_sample (phase * envelope.getSize ());

    phasor_index += phasor_delta * speed;

    output[0] += (1.0f - pan) * out;
    output[1] += pan * out;

}
