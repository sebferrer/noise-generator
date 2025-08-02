#pragma once
#include <JuceHeader.h>
#include "NoiseGenerator.h"

class NoiseRunner {
public:
    static void run(NoiseGenerator& generator,
                    const juce::String& outputFilename,
                    double sampleRate = 44100.0,
                    int durationSeconds = 5,
                    int numChannels = 2,
                    int bitDepth = 16);
};
