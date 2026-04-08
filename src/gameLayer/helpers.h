//
// Created by ddcha on 3/28/2026.
//

#ifndef MYGAME_HELPERS_H
#define MYGAME_HELPERS_H

#pragma once
#include "raylib.h"

Rectangle getTextureAtlas(int x,int y, int cellSizePixelsX,int cellSizePixelsY);
float lerp(float a, float b, float t);
float smoothstep(float t);
#endif //MYGAME_HELPERS_H
