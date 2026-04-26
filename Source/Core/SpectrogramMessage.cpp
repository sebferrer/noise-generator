#include "SpectrogramMessage.h"
#include <cmath>
#include <juce_core/juce_core.h>

SpectrogramMessage::SpectrogramMessage(float sr, Mode mode, float pixelDurationMs) 
    : sampleRate(sr), currentMode(mode) 
{
    samplesPerColumn = (int)(sampleRate * (pixelDurationMs / 1000.0f));

    if (mode == Mode::TextDevLille) {
        numRows = 5;
        int numOscillatorsPerBand = 20; 
        float bandWidth = 800.0f;
        float freqStep = 1000.0f;
        float startFreq = 2000.0f;

        for (int i = 0; i < numRows; ++i) {
            PixelBand band;
            float baseFreq = startFreq + ((numRows - 1 - i) * freqStep); 
            
            for (int o = 0; o < numOscillatorsPerBand; ++o) {
                float freq = baseFreq + (o * (bandWidth / numOscillatorsPerBand));
                band.phases.push_back(0.0f);
                band.phaseIncrements.push_back(juce::MathConstants<float>::twoPi * freq / sampleRate);
            }
            bands.push_back(band);
        }

        std::vector<int> emptySpace(5, 0);

        imageColumns = {
            emptySpace, emptySpace, emptySpace, emptySpace, emptySpace,
            // D
            {1,1,1,1,1}, {1,0,0,0,1}, {0,1,1,1,0}, emptySpace,
            // E
            {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,0,1}, emptySpace,
            // V
            {1,1,0,0,0}, {0,0,1,1,0}, {0,0,0,0,1}, {0,0,1,1,0}, {1,1,0,0,0}, emptySpace,
            // L
            {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, emptySpace,
            // I
            {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, emptySpace,
            // L
            {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, emptySpace,
            // L
            {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, emptySpace,
            // E
            {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,0,1}, emptySpace,
            emptySpace, emptySpace,
            // 2
            {1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}, emptySpace,
            // 0
            {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, emptySpace,
            // 2
            {1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}, emptySpace,
            // 6
            {1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,1,1}, emptySpace,
            emptySpace, emptySpace, emptySpace, emptySpace, emptySpace
        };
    } 
    else if (mode == Mode::QRCode) {
        numRows = 25; 
        int numOscillatorsPerBand = 15; 
        float bandWidth = 700.0f; 
        float freqStep = 750.0f;  
        float startFreq = 500.0f; 

        for (int i = 0; i < numRows; ++i) {
            PixelBand band;
            float baseFreq = startFreq + ((numRows - 1 - i) * freqStep); 
            
            for (int o = 0; o < numOscillatorsPerBand; ++o) {
                float freq = baseFreq + (o * (bandWidth / numOscillatorsPerBand));
                band.phases.push_back(0.0f);
                band.phaseIncrements.push_back(juce::MathConstants<float>::twoPi * freq / sampleRate);
            }
            bands.push_back(band);
        }

        std::vector<int> emptySpace(25, 0);

        imageColumns.insert(imageColumns.end(), 20, emptySpace); 
        
        std::vector<std::vector<int>> qrData = {
            {1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,1,1,1,0,0,0,1,1,1,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,0,0,1,1,0,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1},
            {0,1,0,0,1,0,0,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1},
            {0,1,1,0,0,1,1,1,1,0,1,1,0,0,1,0,1,1,1,0,0,1,0,1,0},
            {1,0,0,0,1,0,0,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1},
            {1,0,1,1,0,1,1,0,0,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,1},
            {1,0,1,1,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0},
            {1,0,0,0,1,1,1,0,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,1,0},
            {0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1},
            {0,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,1,1,1,1,1,0,1,0,1},
            {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0},
            {1,1,1,1,1,1,1,0,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,0,1},
            {1,0,0,0,0,0,1,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,0,1,0},
            {1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0},
            {1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,0,1},
            {1,0,1,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,0,0,0,0,1,1,0},
            {1,0,0,0,0,0,1,0,0,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0},
            {1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1}
        };

        for (const auto& col : qrData) {
            imageColumns.push_back(col);
        }

        imageColumns.insert(imageColumns.end(), 20, emptySpace); 
    }
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
                currentPixelColumn = 0; // Loop the sequence
            }
        }

        const auto& col = imageColumns[currentPixelColumn];

        float sampleVal = 0.0f;
        for (int r = 0; r < numRows; ++r) {
            auto& band = bands[r];
            
            // Adjust amplitude based on the mode so it doesn't clip
            float maxAmp = (currentMode == Mode::QRCode) ? 0.003f : 0.015f;
            band.targetAmplitude = (col[r] == 1) ? maxAmp : 0.0f;
            
            // Smoothing filter
            band.currentAmplitude += (band.targetAmplitude - band.currentAmplitude) * 0.05f;

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
