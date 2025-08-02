#pragma once
#include <JuceHeader.h>

class NoiseGenerator
{
public:
    virtual ~NoiseGenerator() = default;
    virtual void fillBuffer(juce::AudioBuffer<float>& buffer) = 0;
};
