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

struct GameData
{
    GameMap gameMap;

}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();

    gameData.gameMap.create(30,10);

    gameData.gameMap.getBlockUnsafe(0,0).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(1,1).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(2,2).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(3,3).type = Block::dirt;
    gameData.gameMap.getBlockUnsafe(4,4).type = Block::dirt;\


    return true;
}

bool updateGame()
{

    float deltaTime = GetFrameTime();
    if (deltaTime > 1.f/5)
    {
        deltaTime = 1.f/5.f;
    }

    ClearBackground({75,75,150,255});//blue

    for (int y = 0;y < gameData.gameMap.h; y++)
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);

            if (b.type != Block::air)
            {
                float size = 32.0f;
                float posX = size * x;
                float posY = size * y;

                DrawTexturePro(
                    assetManager.dirt,
                    Rectangle{0,0,(float)assetManager.dirt.width, (float)assetManager.dirt.height},//source
                {posX,posY,size,size},//dest
                {0,0},//origin top left corner
                    0,//rotaion
                    WHITE//tint
                 );

            }
        }
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
