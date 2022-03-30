//
// Created by edgallyot on 22/03/2022.
//

#include "GrainGenerator.h"

GrainGenerator::GrainGenerator (Grain* grain, Envelope* envelope, Phasor* phasor)
{
    this->phasor = phasor;
    this->envelope = envelope;
    this->grain = grain;

}
void GrainGenerator::activateGrain (float duration, float speed, float amp, float pan, Grain* p_grain, Envelope* p_envelope)
{
    this->envelope = p_envelope;
    this->grain = p_grain;
    phasor_delta = static_cast<float>( phasor->getSize()) / duration;
    this->speed = speed;
    this->amp = amp;
    this->pan = pan;
    active = true;
}
