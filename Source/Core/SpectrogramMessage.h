#pragma once
#include "NoiseGenerator.h"
#include <vector>

class SpectrogramMessage : public NoiseGenerator {
public:
    SpectrogramMessage(float sampleRate = 44100.0f, float pixelDurationMs = 200.0f);
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float sampleRate;
    
    struct PixelBand {
        std::vector<float> phases;
        std::vector<float> phaseIncrements;
        float currentAmplitude = 0.0f;
        float targetAmplitude = 0.0f;
    };

    std::vector<PixelBand> bands;
    
    int currentPixelColumn = 0;
    int samplesPerColumn; 
    int sampleCounter = 0;

    std::vector<std::vector<int>> imageColumns;
};
