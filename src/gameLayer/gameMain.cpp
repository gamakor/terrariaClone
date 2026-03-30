//
// Created by ddcha on 3/24/2026.
//

#include "gameMain.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <assetManager.h>
#include <cmath>
#include <gameMap.h>
#include <helpers.h>

struct GameData
{
    GameMap gameMap;
    Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();

    gameData.gameMap.create(30,30);

    for (int y = 0;y < gameData.gameMap.h; y++)
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            if (x % 4 == 0 && y % 4 == 0)
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::dirt;
            }
            else if (x % 4 ==0)
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::goldBlock;
            }
            else if (y % 4 == 0 )
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::rubyBlock;
            }
            else
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::woodPlank;
            }
        }


    gameData.camera.target = {0,0}; // world-space center of view
    gameData.camera.rotation = 0.f;
    gameData.camera.zoom = 100.f;

    return true;
}

bool updateGame()
{

    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f/5)
    {
        deltaTime = 1.f/5.f;
    }

    gameData.camera.offset = {GetScreenWidth()/2.f,GetScreenHeight()/2.f};

    ClearBackground({75,75,150,255});//blue

#pragma region camera movement

    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= 3.f * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += 3.f * deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= 3.f * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += 3.f * deltaTime;

#pragma endregion

    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gameData.camera);
    int blockX = (int)floor(worldPos.x);
    int blockY = (int)floor(worldPos.y);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        auto b = gameData.gameMap.getBlockSafe(blockX,blockY);
        if (b)
        {
            *b = {};
        }
    }
     if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
     {
         auto b = gameData.gameMap.getBlockSafe(blockX,blockY);
         if (b)
         {
             b->type = Block::gold;
         }
     }

    BeginMode2D(gameData.camera);

    for (int y = 0;y < gameData.gameMap.h; y++)
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);

            if (b.type != Block::air)
            {

                DrawTexturePro(
                    assetManager.textures,
                    getTextureAtlas(b.type,0,32,32),//source
                {(float)x,(float)y,1,1},//dest
                {0,0},//origin top left corner
                    0,//rotation
                    WHITE//tint
                 );

            }
        }

    DrawTexturePro(
        assetManager.frame,
        {0,0,(float)assetManager.frame.width,(float)assetManager.frame.height},
        {(float)blockX,(float)blockY,1,1},
        {0,0},
        0.f,
        WHITE
        );

    EndMode2D();

    return true;
}

void closeGame()
{
    gameData = {};

    std::cout << "Game Closed! \n";
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nClosed\n";
    f.close();
}
