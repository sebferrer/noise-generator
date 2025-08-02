#include <JuceHeader.h>

int main() {
    const double sampleRate = 44100.0;
    const int numChannels = 2;
    const int durationSeconds = 5;
    const int totalSamples = static_cast<int>(sampleRate * durationSeconds);

    juce::AudioBuffer<float> buffer(numChannels, totalSamples);
    juce::Random random;

    std::cout << "Working directory: "
        << juce::File::getCurrentWorkingDirectory().getFullPathName()
        << std::endl;

    for (int ch = 0; ch < numChannels; ++ch) {
        float* channelData = buffer.getWritePointer(ch);

        for (int i = 0; i < totalSamples; ++i) {
            channelData[i] = random.nextFloat() * 2.0f - 1.0f;
        }
    }

    juce::File outputFile = juce::File::getCurrentWorkingDirectory().getChildFile("noise.wav");
    outputFile.deleteFile();

    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::FileOutputStream> stream(outputFile.createOutputStream());

    if (stream != nullptr) {
        std::unique_ptr<juce::AudioFormatWriter> writer(
            wavFormat.createWriterFor(stream.get(), sampleRate, (unsigned int)numChannels, 16, {}, 0));

        if (writer != nullptr) {
            stream.release();

            writer->writeFromAudioSampleBuffer(buffer, 0, totalSamples);

            std::cout << "File 'noise.wav' written successfully." << std::endl;
        } else {
            std::cerr << "Failed to create WAV writer." << std::endl;
        }
    }
    else {
        std::cerr << "Failed to create output file stream." << std::endl;
    }

    return 0;
}
