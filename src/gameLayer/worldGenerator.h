//
// Created by ddcha on 4/6/2026.
//

#ifndef MYGAME_WORLDGENERATOR_H
#define MYGAME_WORLDGENERATOR_H
#pragma once
#include "gameMap.h"




void generateWorld(GameMap &gameMap, int seed = 1234);
int setHillSize();
void changeHeight(bool isPastHalf);

#endif //MYGAME_WORLDGENERATOR_H