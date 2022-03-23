//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_COSTABLE_H
#define RAINGENERATOR_COSTABLE_H

#include <JuceHeader.h>
#include "Interpolate.h"

class CosTable : public Grain
{
public:
    explicit CosTable (size_t size) :
            Grain (new std::vector<float> (size, 0.0), size),
            max_index (size - 1)
    {
        auto delta = juce::MathConstants<float>::twoPi / static_cast<float>(size);
        auto currentAngle = 0.0f;
        for (size_t i = 0; i < data->size (); ++i)
        {
            (*data)[i] = cos(currentAngle);
            currentAngle += delta;
        }
    }

    float get_sample (float index) override
    {
        index = static_cast<float>(fmod (index, static_cast<double>(max_index)));
        return interpolate<float> (index, *data);
    }

    size_t getMaxIndex () const
    {
        return max_index;
    }

    ~CosTable()
    {
        delete data;
    }
private:
    size_t max_index;
};


#endif //RAINGENERATOR_COSTABLE_H
