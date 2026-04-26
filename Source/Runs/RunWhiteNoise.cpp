#include "../Core/NoiseRunner.h"
#include "../Core/WhiteNoise.h"
#include "../Core/SimplePinkNoise.h"
#include "../Core/PinkNoise.h"
#include "../Core/BrownNoise.h"
#include "../Core/SpectrogramMessage.h"

int main() {
    WhiteNoise whiteNoise(1.0f);
    SimplePinkNoise simplePinkNoise(1.0f);
    BrownNoise brownNoise(1.0f);
    PinkNoise pinkNoise(1.0f, 0.85f, true);
    SpectrogramMessage messageGen(44100.0f, 200.0f);

    // NoiseRunner::run(whiteNoise, "white_noise.wav");
    // NoiseRunner::run(simplePinkNoise, "pink_noise_lowpass.wav");
    // NoiseRunner::run(brownNoise, "brown_noise.wav");
    // NoiseRunner::run(pinkNoise, "pink_noise.wav");

    NoiseRunner::run(messageGen, "secret_message.wav", 44100.0, 15);
    
    return 0;
}
