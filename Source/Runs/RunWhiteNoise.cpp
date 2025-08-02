#include "../Core/WhiteNoise.h"
#include "../Core/NoiseRunner.h"

int main() {
    WhiteNoise noise(1.0f);
    NoiseRunner::run(noise, "white_noise.wav");
    return 0;
}
