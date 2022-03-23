//
// Created by edgallyot on 23/03/2022.
//

#ifndef RAINGENERATOR_PARABOLICRAINGRAIN_H
#define RAINGENERATOR_PARABOLICRAINGRAIN_H

#include "GrainGenerator.h"

class ParabolicRainGrain : public GrainGenerator
{
public:
    ParabolicRainGrain (Grain& grain, Envelope& envelope, Phasor& phasor);
    void getNextSample (float output[]) override;
};


#endif //RAINGENERATOR_PARABOLICRAINGRAIN_H
