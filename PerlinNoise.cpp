#include "PerlinNoise.hpp"


PerlinNoise::PerlinNoise()
{
    this->rng.seed(0); //std::random_device()()
}

void
PerlinNoise::generateWhiteNoise(unsigned int width, unsigned int height,
                                float **arr)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);
    
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            arr[i][j] = (float) dist(this->rng);
        }
    }
}

void
PerlinNoise::generateSmoothNoise(int width, int height, float **base, int octave,
                                 float **smooth)
{
    /*
    float **arr = new float*[height];
    for (int i = 0; i < height; i++)
        arr[i] = new float[width];
    */

    int samplePeriod = 1 << octave;
    float sampleFrequency = 1.0f / samplePeriod;
    for (int i = 0; i < width; i++) {
        // horizontal sampling indices
        int sam_i0 = (i / samplePeriod) * samplePeriod;
        int sam_i1 = (sam_i0 + samplePeriod) % width;
        float horizontalBlend = (i - sam_i0) * sampleFrequency;

        for (int j = 0; j < height; j++) {
            // vertical sampling indices
            int sam_j0 = (j / samplePeriod) * samplePeriod;
            int sam_j1 = (sam_j0 + samplePeriod) % height;
            float verticalBlend = (j - sam_j0) * sampleFrequency;

            // blend two top corners
            float top = this->interpolate(base[sam_i0][sam_j0],
                                          base[sam_i1][sam_j0],
                                          horizontalBlend);
            // blend two bottom corners
            float bot = this->interpolate(base[sam_i0][sam_j1],
                                          base[sam_i1][sam_j1],
                                          verticalBlend);
            smooth[i][j] = interpolate(top, bot, verticalBlend);
        }
    }
    /*
    // Just for testing
    for (int i = 0; i < height; i++)
        delete[] arr[i];
    delete[] arr;
    */
}

float PerlinNoise::interpolate(float x1, float x2, float alpha)
{
    // linear interpolation
    return x1 * (1 - alpha) + alpha * x2;
}

void
PerlinNoise::generatePerlinNoise(int width, int height, float **base,
                                 int octaveCount, float **perlin)
{
    
}
