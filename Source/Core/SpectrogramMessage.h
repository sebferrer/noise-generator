#pragma once
#include "NoiseGenerator.h"
#include <vector>

class SpectrogramMessage : public NoiseGenerator {
public:
    SpectrogramMessage(float sampleRate = 44100.0f);
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float sampleRate;
    
    struct Oscillator {
        float frequency;
        float phase = 0.0f;
        float phaseIncrement = 0.0f;
        float currentAmplitude = 0.0f;
        float targetAmplitude = 0.0f;
    };

    std::vector<Oscillator> oscillators;
    
    int currentPixelColumn = 0;
    int samplesPerColumn; 
    int sampleCounter = 0;

    std::vector<std::vector<int>> imageColumns;
};
