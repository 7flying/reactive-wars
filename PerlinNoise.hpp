#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include <random>
#include <iostream>
#include <utility>


class PerlinNoise {

private:
    std::mt19937 rng;
    
    
public:

    PerlinNoise();

    /** Generates an array with random values between 0 and 1 **/
    void generateWhiteNoise(unsigned int width, unsigned int height, float **arr);

    void generateSmoothNoise(int width, int height, float **base, int octave,
                             float **smooth);

    float interpolate(float x1, float x2, float alpha);

    void generatePerlinNoise(int width, int height, float **base,
                             int octaveCount, float **perlin);

    
    
};

#endif // PERLIN_NOISE_HPP
