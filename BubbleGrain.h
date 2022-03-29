//
// Created by edgallyot on 23/03/2022.
//

#ifndef RAINGENERATOR_BUBBLEGRAIN_H
#define RAINGENERATOR_BUBBLEGRAIN_H

#include "GrainGenerator.h"
#include "CosTable.h"

class BubbleGrain : public GrainGenerator
{
public:
    BubbleGrain (Grain& grain, Envelope& envelope, Phasor& phasor, Envelope& pitchEnvelope);
    void getNextSample (float output[]) override;
    void activateGrain (float duration, float speed, float amp, float pan, Grain& grain, Envelope& envelope) override;
    Envelope& pitchEnvelope;
    Grain& grain;
    float offset{0.0f};
    float ampDelta{0.0f};
    float ampTrigger{0.0f};
    float ampIndex{0.0f};
};


#endif //RAINGENERATOR_BUBBLEGRAIN_H
