#include "WhiteNoise.h"

WhiteNoise::WhiteNoise(float amplitudeIn)
 : amplitude(amplitudeIn) {}

void WhiteNoise::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        float* data = buffer.getWritePointer(ch);

        for (int i = 0; i < numSamples; ++i) {
            data[i] = random.nextFloat() * 2.0f * amplitude - amplitude;
        }
    }
}
