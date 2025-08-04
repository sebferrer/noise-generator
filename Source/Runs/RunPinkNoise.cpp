#include "../Core/PinkNoise.h"
#include "../Core/NoiseRunner.h"

int main() {
    PinkNoise noise(1.0f);

    NoiseRunner::run(noise, "pink_noise.wav", 44100.0, 5, 2, 16);
    
    return 0;
}
