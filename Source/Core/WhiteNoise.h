#pragma once
#include "NoiseGenerator.h"

class WhiteNoise : public NoiseGenerator {
public:
    WhiteNoise(float amplitude = 1.0f);
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float amplitude;
    juce::Random random;
};
