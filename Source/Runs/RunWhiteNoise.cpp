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

    // auto mode = SpectrogramMessage::Mode::Text;
    auto mode = SpectrogramMessage::Mode::QRCode;
    
    float pixelDuration = (mode == SpectrogramMessage::Mode::QRCode) ? 50.0f : 200.0f;

    SpectrogramMessage messageGen(44100.0f, mode, pixelDuration, "DEVLILLE 2026");

    // NoiseRunner::run(whiteNoise, "white_noise.wav");
    // NoiseRunner::run(simplePinkNoise, "pink_noise_lowpass.wav");
    // NoiseRunner::run(brownNoise, "brown_noise.wav");
    // NoiseRunner::run(pinkNoise, "pink_noise.wav");

    NoiseRunner::run(messageGen, "secret_message.wav", 44100.0, 15);
    
    return 0;
}
