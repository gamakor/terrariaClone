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
    Texture2D textures = {};
    Texture2D frame = {};
    Texture2D woodLog = {};


    void loadAll();
};



#endif //MYGAME_ASSETMANAGER_H