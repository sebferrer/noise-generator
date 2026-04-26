#include "SpectrogramMessage.h"
#include <cmath>

SpectrogramMessage::SpectrogramMessage(float sr) : sampleRate(sr) {
    samplesPerColumn = (int)(sampleRate * 0.15f); // 150ms per column (pixel width)

    // Frequencies for our 5 rows (Y axis of the image)
    // Index 0 is the top of the image (highest frequency)
    for (int i = 0; i < 5; ++i) {
        Oscillator osc;
        osc.frequency = 6000.0f - (i * 1000.0f); // 6000, 5000, 4000, 3000, 2000 Hz
        osc.phaseIncrement = juce::MathConstants<float>::twoPi * osc.frequency / sampleRate;
        oscillators.push_back(osc);
    }

    // We draw "HI!" column by column (1 = sine wave ON, 0 = sine wave OFF)
    imageColumns = {
        // Space
        {0,0,0,0,0}, {0,0,0,0,0},
        // H
        {1,1,1,1,1}, {0,0,1,0,0}, {1,1,1,1,1}, {0,0,0,0,0},
        // I
        {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {0,0,0,0,0},
        // !
        {1,1,1,0,1}, {0,0,0,0,0},
        // Space
        {0,0,0,0,0}, {0,0,0,0,0}
    };
}

void SpectrogramMessage::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    // Generate mono audio first
    juce::AudioBuffer<float> temp(1, numSamples);
    float* out = temp.getWritePointer(0);

    for (int i = 0; i < numSamples; ++i) {
        // Move to the next pixel column if enough time has passed
        if (sampleCounter >= samplesPerColumn) {
            sampleCounter = 0;
            currentPixelColumn++;
            if (currentPixelColumn >= imageColumns.size()) {
                currentPixelColumn = 0; // Loop the message forever
            }
        }

        const auto& col = imageColumns[currentPixelColumn];

        float sampleVal = 0.0f;
        for (int r = 0; r < 5; ++r) {
            auto& osc = oscillators[r];
            
            // Set target amplitude based on pixel state
            osc.targetAmplitude = (col[r] == 1) ? 0.15f : 0.0f;

            // Smooth the amplitude to avoid audio clicks when a pixel turns on/off
            osc.currentAmplitude += (osc.targetAmplitude - osc.currentAmplitude) * 0.005f;

            // Generate sine wave
            sampleVal += std::sin(osc.phase) * osc.currentAmplitude;
            
            osc.phase += osc.phaseIncrement;
            if (osc.phase >= juce::MathConstants<float>::twoPi) {
                osc.phase -= juce::MathConstants<float>::twoPi;
            }
        }

        out[i] = sampleVal;
        sampleCounter++;
    }

    // Copy the mono generation to all output channels
    for (int ch = 0; ch < numChannels; ++ch) {
        buffer.copyFrom(ch, 0, temp, 0, 0, numSamples);
    }
}
