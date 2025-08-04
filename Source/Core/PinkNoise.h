#pragma once
#include "NoiseGenerator.h"

class PinkNoise : public NoiseGenerator {
public:
    PinkNoise(float amplitude = 1.0f);

    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float amplitude;
    juce::Random random;
    float state = 0.0f;
};
