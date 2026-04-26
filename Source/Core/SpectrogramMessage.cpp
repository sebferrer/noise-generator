#include "SpectrogramMessage.h"
#include <cmath>
#include <juce_core/juce_core.h>

SpectrogramMessage::SpectrogramMessage(float sr, float pixelDurationMs) : sampleRate(sr) {
    samplesPerColumn = (int)(sampleRate * (pixelDurationMs / 1000.0f));

    int numOscillatorsPerBand = 20; 
    float bandWidth = 800.0f;

    for (int i = 0; i < 5; ++i) {
        PixelBand band;
        float startFreq = 6000.0f - (i * 1000.0f); 
        
        for (int o = 0; o < numOscillatorsPerBand; ++o) {
            float freq = startFreq + (o * (bandWidth / numOscillatorsPerBand));
            band.phases.push_back(0.0f);
            band.phaseIncrements.push_back(juce::MathConstants<float>::twoPi * freq / sampleRate);
        }
        bands.push_back(band);
    }

    imageColumns = {
        {0,0,0,0,0}, {0,0,0,0,0},
        // D
        {1,1,1,1,1}, {1,0,0,0,1}, {0,1,1,1,0}, {0,0,0,0,0},
        // E
        {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,0,1}, {0,0,0,0,0},
        // V
        {1,1,0,0,0}, {0,0,1,1,0}, {0,0,0,0,1}, {0,0,1,1,0}, {1,1,0,0,0}, {0,0,0,0,0},
        // L
        {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,0},
        // I
        {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {0,0,0,0,0},
        // L
        {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,0},
        // L
        {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,0},
        // E
        {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,0,1}, {0,0,0,0,0},
        
        // Space
        {0,0,0,0,0}, {0,0,0,0,0},
        
        // 2
        {1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}, {0,0,0,0,0},
        // 0
        {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,0},
        // 2
        {1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}, {0,0,0,0,0},
        // 6
        {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,1,1}, {0,0,0,0,0},
        
        {0,0,0,0,0}, {0,0,0,0,0}
    };
}

void SpectrogramMessage::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    juce::AudioBuffer<float> temp(1, numSamples);
    float* out = temp.getWritePointer(0);

    for (int i = 0; i < numSamples; ++i) {
        if (sampleCounter >= samplesPerColumn) {
            sampleCounter = 0;
            currentPixelColumn++;
            if (currentPixelColumn >= imageColumns.size()) {
                currentPixelColumn = 0;
            }
        }

        const auto& col = imageColumns[currentPixelColumn];

        float sampleVal = 0.0f;
        for (int r = 0; r < 5; ++r) {
            auto& band = bands[r];
            
            band.targetAmplitude = (col[r] == 1) ? 0.015f : 0.0f;
            band.currentAmplitude += (band.targetAmplitude - band.currentAmplitude) * 0.005f;

            for (size_t o = 0; o < band.phases.size(); ++o) {
                sampleVal += std::sin(band.phases[o]) * band.currentAmplitude;
                band.phases[o] += band.phaseIncrements[o];
                if (band.phases[o] >= juce::MathConstants<float>::twoPi) {
                    band.phases[o] -= juce::MathConstants<float>::twoPi;
                }
            }
        }

        out[i] = sampleVal;
        sampleCounter++;
    }

    for (int ch = 0; ch < numChannels; ++ch) {
        buffer.copyFrom(ch, 0, temp, 0, 0, numSamples);
    }
}
