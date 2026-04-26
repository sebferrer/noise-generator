#include "PinkNoise.h"

PinkNoise::PinkNoise(float amplitudeIn, float softnessIn, bool useLowpassFilterIn)
    : amplitude(amplitudeIn),
      softness(juce::jlimit(0.0f, 1.0f, softnessIn)),
      useLowpassFilter(useLowpassFilterIn)
{
    smoothing = softness * 0.999f;
}

void PinkNoise::fillBuffer(juce::AudioBuffer<float>& buffer) {
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int ch = 0; ch < numChannels; ++ch) {
        float* data = buffer.getWritePointer(ch);
        filterState = 0.0f;

        for (int i = 0; i < numSamples; ++i) {
            // Voss-McCartney pink noise
            int changedRow = 0;
            ++counter;
            int tmp = counter;
            while ((tmp & 1) == 0 && changedRow < numRows) {
                ++changedRow;
                tmp >>= 1;
            }

            if (changedRow < numRows) {
                float newRand = random.nextFloat() * 2.0f - 1.0f;
                runningSum -= randomRows[changedRow];
                randomRows[changedRow] = newRand;
                runningSum += newRand;
            }

            float pink = runningSum / static_cast<float>(numRows);

            // Soft filtering depending on softness
            if (useLowpassFilter) {
                filterState = smoothing * filterState + (1.0f - smoothing) * pink;
                data[i] = amplitude * filterState;
            } else {
                data[i] = amplitude * pink;
            }
        }
    }
}
