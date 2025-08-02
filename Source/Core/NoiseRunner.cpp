#include "NoiseRunner.h"

void NoiseRunner::run(NoiseGenerator& generator,
                      const juce::String& outputFilename,
                      double sampleRate,
                      int durationSeconds,
                      int numChannels,
                      int bitDepth) {
    const int totalSamples = static_cast<int>(sampleRate * durationSeconds);
    juce::AudioBuffer<float> buffer(numChannels, totalSamples);

    generator.fillBuffer(buffer);

    juce::File outputDir = juce::File::getCurrentWorkingDirectory().getChildFile("Output");
    outputDir.createDirectory();

    juce::File outputFile = outputDir.getChildFile(outputFilename);
    outputFile.deleteFile();

    juce::WavAudioFormat format;
    if (auto stream = outputFile.createOutputStream()) {
        if (auto writer = format.createWriterFor(stream.get(), sampleRate, numChannels, bitDepth, {}, 0)) {
            stream.release();
            writer->writeFromAudioSampleBuffer(buffer, 0, totalSamples);
            std::cout << outputFilename << " written to " << outputFile.getFullPathName() << std::endl;
        } else {
            std::cerr << "Failed to create WAV writer." << std::endl;
        }
    } else {
        std::cerr << "Failed to create output stream." << std::endl;
    }
}
