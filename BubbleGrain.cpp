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
    // TODO Complete the DSP 4 Bubbles
    auto phase = phasor.get_sample (phasor_index);
    auto pitchEnvelope = envelope.get_sample (phase * envelope.getSize ());
    auto offset = duration;

    cosTable.get_sample(0.0f);

    phasor_index += phasor_delta * speed;

    auto out = 0.0f;

    output[0] += (1.0f - pan) * out * amp;
    output[1] += pan * out * amp;

}
