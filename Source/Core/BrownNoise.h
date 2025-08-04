#pragma once
#include "NoiseGenerator.h"

class BrownNoise : public NoiseGenerator {
public:
    BrownNoise(float amplitude = 1.0f);

    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float amplitude;
    juce::Random random;
    float lastValue = 0.0f;
};
