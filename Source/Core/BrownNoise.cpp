#include "BrownNoise.h"

BrownNoise::BrownNoise(float amplitudeIn)
    : amplitude(amplitudeIn) {}

void BrownNoise::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        float* data = buffer.getWritePointer(ch);
        float value = 0.0f;

        for (int i = 0; i < numSamples; ++i) {
            float white = random.nextFloat() * 2.0f - 1.0f;
            value += white * 0.02f;
            value = juce::jlimit(-1.0f, 1.0f, value); // Clamp
            data[i] = amplitude * value;
        }
    }
}
