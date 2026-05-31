# Noise Generator

An audio noise generator written in C++ using the JUCE framework. It allows you to generate various types of noise and export them directly to a WAV file.

## Code Architecture

The core of the system relies on a `NoiseGenerator` interface. It defines a `fillBuffer` method that each noise algorithm implements to fill the audio buffer.

To handle the export, we use the `NoiseRunner` class. It takes a generator as a parameter, manages the audio rendering for a specific duration, and writes the output to a file.

The `Source/Runs/RunWhiteNoise.cpp` file serves as the entry point. This is where the different noises are initialized and the generation is triggered.

## Available Noises

You'll find the classics of audio generation:
* White noise
* White noise + lowpass filter
* Pink noise (with or without lowpass filter)
* Brown noise

There's also a special generator called `SpectrogramMessage`. Instead of producing standard noise, it generates an audio signal designed to display text or a QR code when you view the file through a spectrogram.

## How to Build and Run

The project is configured using CMake. First, configure the project and build it:
```bash
cmake -B cmake-build
cmake --build cmake-build --config Debug
```

Once the build is complete, you can run the generated executable.