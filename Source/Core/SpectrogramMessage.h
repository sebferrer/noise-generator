#pragma once
#include "NoiseGenerator.h"
#include <vector>

class SpectrogramMessage : public NoiseGenerator {
public:
    enum class Mode {
        TextDevLille,
        QRCode
    };

    SpectrogramMessage(float sampleRate = 44100.0f, Mode mode = Mode::QRCode, float pixelDurationMs = 50.0f);
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float sampleRate;
    Mode currentMode;
    int numRows;
    
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
