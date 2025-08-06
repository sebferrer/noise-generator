#pragma once

#include "NoiseGenerator.h"
#include <array>

class PinkNoise : public NoiseGenerator {
public:
    PinkNoise(float amplitudeIn = 1.0f, float softnessIn = 0.8f); // [0.0 - 1.0]
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float amplitude;
    float softness;
    float smoothing;
    juce::Random random;

    // Voss-McCartney state
    int numRows = 16;
    std::array<float, 16> randomRows{};
    int counter = 0;
    float runningSum = 0.0f;

    // Post-filter state
    float filterState = 0.0f;
};
