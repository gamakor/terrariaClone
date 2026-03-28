//
// Created by ddcha on 3/28/2026.
//

#ifndef MYGAME_GAMEMAP_H
#define MYGAME_GAMEMAP_H

#pragma once
#include <vector>
#include <blocks.h>

struct GameMap
{
    int w = 0;
    int h = 0;

    std::vector<Block> mapData;

    void create(int w, int h);

    Block &getBlockUnsafe(int x, int y);
    Block *getBlockSafe(int x, int y);
};

#endif //MYGAME_GAMEMAP_H