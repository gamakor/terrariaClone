//
// Created by ddcha on 3/28/2026.
//

#ifndef MYGAME_ASSETMANAGER_H
#define MYGAME_ASSETMANAGER_H
#pragma once
#include "raylib.h"

struct AssetManager
{
    Texture2D dirt = {};

    void loadAll();
};



#endif //MYGAME_ASSETMANAGER_H