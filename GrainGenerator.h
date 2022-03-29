//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_GRAINGENERATOR_H
#define RAINGENERATOR_GRAINGENERATOR_H

#include "Interpolate.h"
#include "Phasor.h"
#include "Envelope.h"
#include <JuceHeader.h>

class GrainGenerator
{
public:
    GrainGenerator (Grain& grain, Envelope& envelope, Phasor& phasor);
    virtual void activateGrain (float duration, float speed, float amp, float pan, Grain& grain, Envelope& envelope);
    virtual void getNextSample (float output[]) = 0;
    [[nodiscard]] bool isActive () const
    { return active; };
protected:
    bool active {false};
    float pan {0.0f};
    float duration {0.0f};
    float speed {0.0f};
    float amp {0.0f};
    Phasor& phasor;
    Envelope& envelope;
    float phasor_index {0.0f};
    float phasor_delta {0.0f};
    Grain& grain;
};


#endif //RAINGENERATOR_GRAINGENERATOR_H
