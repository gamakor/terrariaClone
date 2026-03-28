//
// Created by ddcha on 3/24/2026.
//

#include "gameMain.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <assetManager.h>
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

    gameData.gameMap.create(30,10);

    gameData.gameMap.getBlockUnsafe(0,0).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1,1).type = Block::grass;
    gameData.gameMap.getBlockUnsafe(2,2).type = Block::goldBlock;
    gameData.gameMap.getBlockUnsafe(3,3).type = Block::glass;
    gameData.gameMap.getBlockUnsafe(4,4).type = Block::platform;

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
                    0,//rotaion
                    WHITE//tint
                 );

            }
        }
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
