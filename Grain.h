//
// Created by edgallyot on 22/03/2022.
//

#ifndef RAINGENERATOR_GRAIN_H
#define RAINGENERATOR_GRAIN_H

#include <cstddef>
#include "Interpolate.h"

class Grain
{
public:
    explicit Grain (std::vector<float>* vec, size_t size) : data (vec), m_size (size)
    {};
    virtual float get_sample (float index) = 0;
    size_t getSize () const
    {
        return m_size;
    }
protected:
    std::vector<float>* data;
    size_t m_size;
};


#endif //RAINGENERATOR_GRAIN_H
