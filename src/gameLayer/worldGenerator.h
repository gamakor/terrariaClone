//
// Created by ddcha on 4/6/2026.
//

#ifndef MYGAME_WORLDGENERATOR_H
#define MYGAME_WORLDGENERATOR_H
#pragma once
#include "gameMap.h"


inline std::vector<float> dirtEndResultNoiseMap;
inline std::vector<float> stoneEndResultNoiseMap;
void generateWorld(GameMap &gameMap, int seed = 1234);

float getNoise(int blockType,int x);

inline float noiseMap = 0.f;



#endif //MYGAME_WORLDGENERATOR_H