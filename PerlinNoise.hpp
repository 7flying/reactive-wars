#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include <math.h>
#include <random>
#include <iostream>
#include <utility>


class PerlinNoise {

private:
    std::mt19937 rng;

    /** Generates an array with random values between 0 and 1 **/
    void generateWhiteNoise(unsigned int width, unsigned int height, float **arr);

    /** Performs the smoothing **/
    void generateSmoothNoise(int width, int height, float **base, int octave,
                             float **smooth);
    /** Linear interpolation function  **/
    float interpolate(float x1, float x2, float alpha);

public:

    PerlinNoise();
    /** Given an 2D array of widht x heigh (perlin) generates Perlin Noise **/
    void generatePerlinNoise(int width, int height, int octaveCount,
                             float persistance, float **perlin);

    /** Test implementation **/
    void test();

};

#endif // PERLIN_NOISE_HPP
