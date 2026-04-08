//
// Created by ddcha on 3/28/2026.
//

#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY)
{
    return Rectangle{(float)x * cellSizePixelsX, (float)y * cellSizePixelsY,
        (float)cellSizePixelsX,(float)cellSizePixelsY};
}

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}
//smooth step for lerps
float smoothstep(float t)
{
    return t * t * (3 - 2 * t);
}
