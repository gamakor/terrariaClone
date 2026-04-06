//
// Created by ddcha on 3/24/2026.
//
#pragma once
#ifndef MYGAME_GAMEMAIN_H
#define MYGAME_GAMEMAIN_H

#include <blocks.h>

bool initGame();
bool updateGame();

void closeGame();

void renderWoodLog(Block &b, int x, int y);


#endif //MYGAME_GAMEMAIN_H