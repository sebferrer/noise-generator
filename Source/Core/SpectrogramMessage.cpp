#include "SpectrogramMessage.h"
#include <cmath>
#include <juce_core/juce_core.h>
#include <cctype>

namespace {
    std::vector<std::vector<int>> getCharColumns(char c) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        switch(c) {
            case 'A': return {{1,1,1,1,1}, {1,0,1,0,0}, {1,1,1,1,1}};
            case 'B': return {{1,1,1,1,1}, {1,0,1,0,1}, {0,1,0,1,0}};
            case 'C': return {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,0,0,1}};
            case 'D': return {{1,1,1,1,1}, {1,0,0,0,1}, {0,1,1,1,0}};
            case 'E': return {{1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,0,1}};
            case 'F': return {{1,1,1,1,1}, {1,0,1,0,0}, {1,0,1,0,0}};
            case 'G': return {{0,1,1,1,0}, {1,0,0,0,1}, {1,0,1,1,1}};
            case 'H': return {{1,1,1,1,1}, {0,0,1,0,0}, {1,1,1,1,1}};
            case 'I': return {{1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}};
            case 'J': return {{0,0,0,1,1}, {1,0,0,0,1}, {1,1,1,1,0}};
            case 'K': return {{1,1,1,1,1}, {0,0,1,0,0}, {0,1,0,1,0}, {1,0,0,0,1}};
            case 'L': return {{1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}};
            case 'M': return {{1,1,1,1,1}, {0,1,0,0,0}, {0,0,1,0,0}, {0,1,0,0,0}, {1,1,1,1,1}};
            case 'N': return {{1,1,1,1,1}, {0,1,0,0,0}, {0,0,1,0,0}, {0,0,0,1,0}, {1,1,1,1,1}};
            case 'O': return {{0,1,1,1,0}, {1,0,0,0,1}, {0,1,1,1,0}};
            case 'P': return {{1,1,1,1,1}, {1,0,1,0,0}, {0,1,0,0,0}};
            case 'Q': return {{0,1,1,1,0}, {1,0,0,0,1}, {0,1,1,1,1}};
            case 'R': return {{1,1,1,1,1}, {1,0,1,0,0}, {0,1,0,1,1}};
            case 'S': return {{0,1,1,0,1}, {1,0,1,0,1}, {1,0,0,1,0}};
            case 'T': return {{1,0,0,0,0}, {1,1,1,1,1}, {1,0,0,0,0}};
            case 'U': return {{1,1,1,1,0}, {0,0,0,0,1}, {1,1,1,1,0}};
            case 'V': return {{1,1,0,0,0}, {0,0,1,1,0}, {0,0,0,0,1}, {0,0,1,1,0}, {1,1,0,0,0}};
            case 'W': return {{1,1,1,1,1}, {0,0,0,1,0}, {0,0,1,0,0}, {0,0,0,1,0}, {1,1,1,1,1}};
            case 'X': return {{1,0,0,0,1}, {0,1,0,1,0}, {0,0,1,0,0}, {0,1,0,1,0}, {1,0,0,0,1}};
            case 'Y': return {{1,1,0,0,0}, {0,0,1,0,0}, {0,0,0,1,1}, {0,0,1,0,0}, {1,1,0,0,0}};
            case 'Z': return {{1,0,0,1,1}, {1,0,1,0,1}, {1,1,0,0,1}};
            case '0': return {{1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}};
            case '1': return {{0,1,0,0,0}, {1,1,1,1,1}, {0,0,0,0,0}};
            case '2': return {{1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}};
            case '3': return {{1,0,1,0,1}, {1,0,1,0,1}, {1,1,1,1,1}};
            case '4': return {{1,1,1,0,0}, {0,0,1,0,0}, {1,1,1,1,1}};
            case '5': return {{1,1,1,0,1}, {1,0,1,0,1}, {1,0,1,1,1}};
            case '6': return {{1,1,1,1,1}, {1,0,1,0,1}, {1,0,1,1,1}};
            case '7': return {{1,0,0,0,0}, {1,0,0,0,0}, {1,1,1,1,1}};
            case '8': return {{1,1,1,1,1}, {1,0,1,0,1}, {1,1,1,1,1}};
            case '9': return {{1,1,1,0,1}, {1,0,1,0,1}, {1,1,1,1,1}};
            case ' ': return {{0,0,0,0,0}, {0,0,0,0,0}};
            default: return {};
        }
    }
}

SpectrogramMessage::SpectrogramMessage(float sr, Mode mode, float pixelDurationMs, const std::string& text) 
    : sampleRate(sr), currentMode(mode), textMessage(text) 
{
    samplesPerColumn = (int)(sampleRate * (pixelDurationMs / 1000.0f));

    if (mode == Mode::Text) {
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
        imageColumns.insert(imageColumns.end(), 5, emptySpace); // padding

        for (char c : textMessage) {
            auto cols = getCharColumns(c);
            if (!cols.empty()) {
                for (const auto& col : cols) {
                    imageColumns.push_back(col);
                }
                imageColumns.push_back(emptySpace); // space between letters
            }
        }

        imageColumns.insert(imageColumns.end(), 5, emptySpace); // padding
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
        
        // QR code for https://kimi.ovh/noise (transposed: each row = one spectrogram column)
        std::vector<std::vector<int>> qrData = {
            {1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,0,0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,1,0,1,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0},
            {1,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0,1,0,1,1,0,0,1,1},
            {0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,0},
            {0,0,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,1,0,0,1,1,1,0},
            {0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,0},
            {0,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1},
            {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1},
            {1,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,0},
            {1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,1,0,0,0,0,0,0,1,0},
            {1,1,0,1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,1,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,1,1,1,1},
            {1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1},
            {1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0},
            {1,0,1,1,1,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0},
            {1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,0,1,1,0,1,1,0},
            {1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1},
            {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,1}
        };

        std::vector<std::vector<int>> qrData2 = {
            {1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,0,1},
            {1,0,1,1,1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1},
            {1,0,1,1,1,0,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,1,1,0,1},
            {1,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0},
            {1,1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,1,0,0,0},
            {0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,0},
            {1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
            {0,1,1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1},
            {1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,1},
            {1,1,1,0,1,0,0,0,1,1,1,0,1,1,0,1,1,0,0,1,0,0,0,1,0},
            {1,0,0,1,1,1,1,0,1,0,1,0,0,0,0,1,1,1,0,1,1,1,0,1,1},
            {1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,0,1},
            {1,0,0,0,0,1,1,1,0,0,1,0,1,1,0,0,1,1,1,1,1,0,1,0,0},
            {0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0},
            {1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1},
            {1,0,0,0,0,0,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,0,0,0},
            {1,0,1,1,1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,1,1,1},
            {1,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1},
            {1,0,1,1,1,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,0,1,1,0,1},
            {1,0,0,0,0,0,1,0,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,1},
            {1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,0,0,1,0,0,1}
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
