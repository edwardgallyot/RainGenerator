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
    BubbleGrain (Grain& grain,
                 Envelope& envelope,
                 Phasor& phasor,
                 Envelope& pitchEnvelope,
                 CosTable& cosTable);
    void getNextSample (float output[]) override;
    CosTable& cosTable;
    Envelope& pitchEnvelope;

};


#endif //RAINGENERATOR_BUBBLEGRAIN_H
