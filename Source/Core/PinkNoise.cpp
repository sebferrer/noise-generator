#include "PinkNoise.h"

PinkNoise::PinkNoise(float amplitudeIn)
    : amplitude(amplitudeIn) {}

void PinkNoise::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        float* data = buffer.getWritePointer(ch);
        float previous = 0.0f;

        for (int i = 0; i < numSamples; ++i) {
            float white = random.nextFloat() * 2.0f - 1.0f;
            previous = 0.98f * previous + 0.02f * white;  // Simple low-pass filter
            data[i] = amplitude * previous;
        }
    }
}
