//
// Created by ddcha on 4/3/2026.
//

#include "randomstuff.h"

float getRandomFloat(std::ranlux24_base &rng, float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

int getRandomInt(std::ranlux24_base &rng, int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

bool getRandomChance(std::ranlux24_base &rng, float chance)
{
    float dice = getRandomFloat(rng, 0.0, 1.0);
    return dice <= chance;
}

unsigned int hash2D(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (unsigned int)(n * (n * n * 15731 + 789221) + 1376312589);
}

int randomTile(int x, int y)
{
    return hash2D(x, y) % 4;
}
