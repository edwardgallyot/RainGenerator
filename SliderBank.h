//
// Created by edgallyot on 14/03/2022.
//

#ifndef PINGPONGED_SLIDERBANK_H
#define PINGPONGED_SLIDERBANK_H

#include <JuceHeader.h>
#include <atomic>
#include "RainGeneratorProcessor.h"
#include "RainGeneratorSlider.h"

class SliderBank : public juce::Component
{
public:
    SliderBank (RainGeneratorProcessor& p, juce::AudioProcessorValueTreeState& vts,
                std::vector<std::string> idName1, std::vector<std::string> idName2);
    void resized() override;
private:
    RainGeneratorProcessor& processor;
    juce::AudioProcessorValueTreeState& parameters;
    RainGeneratorSlider slider1;
    RainGeneratorSlider slider2;
};


#endif //PINGPONGED_SLIDERBANK_H
