//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_NOISE_H
#define RAINGENERATOR_NOISE_H

#include <random>

class Noise : public Grain
{
public:
    explicit Noise (size_t size) :
            Grain (new std::vector<float> (size, 0.0), size),
            max_index (size - 1)
    {
        std::default_random_engine generator;
        std::normal_distribution<float> distribution (0.0f, 0.4f);

        for (size_t i = 0; i < data->size (); ++i)
        {
            (*data)[i] = distribution (generator);
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

    ~Noise ()
    {
        delete data;
    }
private:
    size_t max_index;
};


#endif //RAINGENERATOR_NOISE_H
