//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_ENVELOPE_H
#define RAINGENERATOR_ENVELOPE_H

#include "Grain.h"
#include "id_name_vts.h"
#include <JuceHeader.h>

class Envelope : public Grain
{
public:
    explicit Envelope (size_t size, Envelopes* type_p) :
            Grain (new std::vector<float> (size, 0.0), size),
            max_index (size - 1),
            type (type_p)
    {
        switch (*type)
        {
            case Envelopes::Parabolic:
            {
                auto amplitude = 0.0f;
                auto parabola_size = static_cast<float>(max_index);
                auto rdur = 1.0f / parabola_size;
                auto rdur2 = rdur * rdur;
                auto slope = 4.0f * 1.0f * (rdur - rdur2);
                auto curve = -8.0f * 1.0f * rdur2;

                for (float & i : *data)
                {
                    if (amplitude < 0.0f)
                        amplitude = 0.0f;
                    i = amplitude;
                    amplitude += slope;
                    slope += curve;
                }
                break;
            };
            case Envelopes::Exponential:
            {
                for (size_t i = 0; i < data->size (); ++i)
                {
                    (*data)[i] =  static_cast<float>(i) / static_cast<float>(max_index);
                    (*data)[i] = pow((*data)[i], 2.0f);
                }
                break;
            };
            case Envelopes::Guassian:
            {
                for (size_t i = 0; i < data->size (); ++i)
                {
                    auto o = 0.4f;
                    auto u = 0.5f;
                    auto coeff = 1 / (o * sqrt (juce::MathConstants<float>::twoPi));
                    (*data)[i] =  static_cast<float>(i) / static_cast<float>(max_index);
                    (*data)[i] = coeff * exp(-0.5f * pow((((*data)[i] - u)/ pow(o, 2.0f)), 2.0f));
                }
                break;
            };
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

    ~Envelope ()
    {
        delete data;
    }
private:
    size_t max_index;
    Envelopes* type;
};


#endif //RAINGENERATOR_ENVELOPE_H
