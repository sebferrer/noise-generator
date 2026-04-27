#pragma once
#include "NoiseGenerator.h"
#include <vector>
#include <string>

class SpectrogramMessage : public NoiseGenerator {
public:
    enum class Mode {
        Text,
        QRCode
    };

    SpectrogramMessage(float sampleRate = 44100.0f, Mode mode = Mode::Text, float pixelDurationMs = 50.0f, const std::string& text = "DEVLILLE 2026");
    void fillBuffer(juce::AudioBuffer<float>& buffer) override;

private:
    float sampleRate;
    Mode currentMode;
    int numRows;
    std::string textMessage;
    
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
