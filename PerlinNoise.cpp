#include "PerlinNoise.hpp"


PerlinNoise::PerlinNoise()
{
    this->rng.seed(std::random_device()());
}

int PerlinNoise::randomValue(int from, int to)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to);
    return (int) dist(this->rng);
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
    //int samplePeriod = 1 << octave;
    int samplePeriod = pow(2, octave);
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
}

float PerlinNoise::interpolate(float x1, float x2, float alpha)
{
    // linear interpolation
    return x1 * (1 - alpha) + alpha * x2;
}

void
PerlinNoise::generatePerlinNoise(int width, int height, int octaveCount,
                                 float persistance, float **perlin)
{
    // Generate base white noise
    float **base = new float*[height];
    for (int i = 0; i < height; i++)
        base[i] = new float[width];
    this->generateWhiteNoise(width, height, base);

    float ***smoothNoise = new float**[octaveCount];

    for (int i = 0; i < octaveCount; i++) {
        smoothNoise[i] = new float*[height];
        for (int j = 0; j < height; j++)
            smoothNoise[i][j] = new float[width];
        this->generateSmoothNoise(width, height, base, i, smoothNoise[i]);
    }
    float amplitude = 1.0f;
    float totalAmplitude = 0.0f;

    float min = 1.0f;
    float max = 0.0f;
    bool first = false;
    // blend noise
    for (int octave = octaveCount - 1; octave >= 0; octave--) {
        amplitude *= persistance;
        totalAmplitude += amplitude;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                perlin[i][j] += smoothNoise[octave][i][j] * amplitude;
                if (!std::isinf(std::abs(perlin[i][j])) &&
                    !std::isnan(std::abs(perlin[i][j])))
                {
                    if (first) {
                        min = perlin[i][j];
                        max = perlin[i][j];
                        first = false;
                    }
                    if (perlin[i][j] < min)
                        min = perlin[i][j];
                    if (perlin[i][j] > max)
                        max = perlin[i][j];
                }
            }
        }
    }
    
    // normalise
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (totalAmplitude > 0)
                perlin[i][j] /= totalAmplitude;
            if (perlin[i][j] < 0.0f || perlin[i][j] > 1.0f) {
                perlin[i][j] = (perlin[i][j] - min) / (max - min);
            }
        }
    }
    
    // Clean up base and smooth noise for each octave
    for (int i = 0; i < height; i++) {
        delete[] base[i];
    }
    delete[] base;
    // Tridimensional
    for (int i = 0; i < octaveCount; i++) {
        for (int j = 0; j < height; j++)
            delete[] smoothNoise[i][j];
        delete[] smoothNoise[i];
    }
    delete[] smoothNoise;
}


void PerlinNoise::test()
{
    int width = 32;
    int height = 32;
    
    PerlinNoise perlin;
    float **ret = new float*[height];
    for (int i = 0; i < height; i++)
        ret[i] = new float[width];

    perlin.generatePerlinNoise(width, height, 2, 1.0f, ret);
    std::cout << "Generating Perlin Noise" << std::endl << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << ret[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Cleanup
    // free base & smooth
    for (int i = 0; i < height; i++)
        delete[] ret[i];
    delete[] ret;

}
