#include "../Core/BrownNoise.h"
#include "../Core/NoiseRunner.h"

int main() {
    BrownNoise noise(1.0f);

    NoiseRunner::run(noise, "brown_noise.wav", 44100.0, 5, 2, 16);
    
    return 0;
}
