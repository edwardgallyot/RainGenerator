//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_PHASOR_H
#define RAINGENERATOR_PHASOR_H

#include "Interpolate.h"
#include "Grain.h"
#include <JuceHeader.h>


class Phasor : public Grain
{
public:
    explicit Phasor (size_t size) :
            Grain (new std::vector<float> (size, 0.0), size),
            max_index (size - 1)
    {
        for (size_t i = 0; i < data->size (); ++i)
        {
            (*data)[i] = static_cast<float>(i) / static_cast<float>(max_index);
        }
    }
    float get_sample (float index) override
    {
        return interpolate<float> (index, *data);
    }

    size_t getMaxIndex () const
    {
        return max_index;
    }

    ~Phasor ()
    {
        delete data;
    }
private:
    size_t max_index;
};


#endif //RAINGENERATOR_PHASOR_H
