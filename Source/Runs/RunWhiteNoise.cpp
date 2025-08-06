#include "../Core/WhiteNoise.h"
#include "../Core/NoiseRunner.h"
#include "../Core/PinkNoise.h"
#include "../Core/BrownNoise.h"

int main() {
    WhiteNoise whiteNoise(1.0f);
    PinkNoise pinkNoise(1.0f);
    BrownNoise brownNoise(1.0f);

    NoiseRunner::run(whiteNoise, "white_noise.wav");
    NoiseRunner::run(pinkNoise, "pink_noise.wav");
    NoiseRunner::run(brownNoise, "brown_noise.wav");
    
    return 0;
}
