#include "../Core/NoiseRunner.h"
#include "../Core/WhiteNoise.h"
#include "../Core/SimplePinkNoise.h"
#include "../Core/PinkNoise.h"
#include "../Core/BrownNoise.h"

int main() {
    WhiteNoise whiteNoise(1.0f);
    SimplePinkNoise simplePinkNoise(1.0f);
    BrownNoise brownNoise(1.0f);
    PinkNoise pinkNoise(1.0f, 0.85f);

    // NoiseRunner::run(whiteNoise, "white_noise.wav");
    // NoiseRunner::run(simplePinkNoise, "pink_noise_lowpass.wav");
    // NoiseRunner::run(brownNoise, "brown_noise.wav");
    NoiseRunner::run(pinkNoise, "pink_noise.wav");
    
    return 0;
}
