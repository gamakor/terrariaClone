//
// Created by ddcha on 3/28/2026.
//

#include "assetManager.h"

void AssetManager::loadAll()
{
    dirt = LoadTexture(RESOURCES_PATH "dirt.png");

    textures = LoadTexture(RESOURCES_PATH "textures.png");

    frame = LoadTexture(RESOURCES_PATH "frame.png");
}
