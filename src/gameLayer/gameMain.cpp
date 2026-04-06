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
#include <imgui.h>
#include <rlImGui.h>

#include "randomstuff.h"
#include "raymath.h"
#include "worldGenerator.h"


struct GameData
{
    GameMap gameMap;
    Camera2D camera;
}gameData;

AssetManager assetManager;

bool initGame()
{
    assetManager.loadAll();

    gameData.gameMap.create(900,500);

    generateWorld(gameData.gameMap);
    /*for (int y = 0;y < gameData.gameMap.h; y++)
        for (int x = 0; x < gameData.gameMap.w; x++)
        {
            if (x % 4 == 0 && y % 4 == 0)
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::dirt;
                gameData.gameMap.getBackgroundBlockUnsafe(x,y).type = Block::dirtWall;
            }
            else if (x % 4 ==0)
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::goldBlock;
                gameData.gameMap.getBackgroundBlockUnsafe(x,y).type = Block::goldBlockWall;
            }
            else if (y % 4 == 0 )
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::rubyBlock;
                gameData.gameMap.getBackgroundBlockUnsafe(x,y).type = Block::rubyBlockWall;
            }
            else
            {
                gameData.gameMap.getBlockUnsafe(x,y).type = Block::woodPlank;
                gameData.gameMap.getBackgroundBlockUnsafe(x,y).type = Block::woodWall;
            }
        }*/


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

#pragma region imgui Window
    ImGui::Begin("test");
    static int selectedBlock = 0;
    ImGui::RadioButton("WoodLog",&selectedBlock,Block::woodLog);
    ImGui::RadioButton("Leaves",&selectedBlock,Block::leaves);
    ImGui::RadioButton("stone",&selectedBlock,Block::stone);
    ImGui::RadioButton("sand",&selectedBlock,Block::sand);

    ImGui::End();
#pragma endregion

#pragma region camera movement
    static float CAMERA_SPEED = 10.f;
    if (IsKeyDown(KEY_LEFT)) gameData.camera.target.x -= CAMERA_SPEED * deltaTime;
    if (IsKeyDown(KEY_RIGHT)) gameData.camera.target.x += CAMERA_SPEED * deltaTime;
    if (IsKeyDown(KEY_UP)) gameData.camera.target.y -= CAMERA_SPEED * deltaTime;
    if (IsKeyDown(KEY_DOWN)) gameData.camera.target.y += CAMERA_SPEED * deltaTime;

#pragma endregion

#pragma region imGui camera
    ImGui::Begin("camera");
    ImGui::SliderFloat("Camera Speed",&CAMERA_SPEED,1.f,50.f);
    ImGui::SliderFloat("Camera Zoom",&gameData.camera.zoom,1.f,100.f);
    ImGui::End();
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
             b->type = selectedBlock;
         }
     }

    BeginMode2D(gameData.camera);

    Vector2 topLeftView = GetScreenToWorld2D({0,0},gameData.camera);
    Vector2 bottomRightView = GetScreenToWorld2D({(float)GetScreenWidth(),(float)GetScreenHeight()},gameData.camera);

    int startXView = (int)floorf(topLeftView.x - 1);
    int endXView = (int)floorf(bottomRightView.x + 1);
    int startYView = (int)floorf(topLeftView.y - 1);
    int endYView = (int)floorf(bottomRightView.y + 1);

    startXView = Clamp(startXView,0,gameData.gameMap.w-1);
    endXView = Clamp(endXView,0,gameData.gameMap.w-1);

    startYView = Clamp(startYView,0,gameData.gameMap.h-1);
    endYView = Clamp(endYView,0,gameData.gameMap.h-1);

    for (int y = startYView; y < endYView; y++)
        for (int x = startXView; x < endXView; x++)
        {
            //draw background mapp
            auto &a = gameData.gameMap.getBackgroundBlockUnsafe(x,y);

            if (a.type != Block::air)
            {
                DrawTexturePro(
                            assetManager.textures,
                            getTextureAtlas(a.type,randomTile(x,y),32,32),//source
                        {(float)x,(float)y,1,1},//dest
                        {0,0},//origin top left corner
                            0,//rotation
                            WHITE//tint
                         );
            }


            //draw foreground map
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);

            if (b.type != Block::air)
            {

                if (b.type == Block::woodLog)
                {
                   renderWoodLog(b,x,y);
                }else
                {
                    DrawTexturePro(
                        assetManager.textures,
                        getTextureAtlas(b.type,randomTile(x,y),32,32),//source
                    {(float)x,(float)y,1,1},//dest
                    {0,0},//origin top left corner
                        0,//rotation
                        WHITE//tint
                     );
                }

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
    DrawFPS(10,10);
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

void renderWoodLog(Block &b, int x, int y)
{
                    auto leftBlock = gameData.gameMap.getBlockSafe((x-1),y);
                    auto rightBlock = gameData.gameMap.getBlockSafe((x+1),y);
                    auto upBlock = gameData.gameMap.getBlockSafe(x,y-1);
                    auto downBlock = gameData.gameMap.getBlockSafe(x,y+1);



                    //Write comments that descrip what each thing is doing.

                    if (downBlock->type == Block::woodLog && leftBlock->type == Block::leaves  && rightBlock->type == Block::leaves)
                    {
                        DrawTexturePro(
                        assetManager.woodLog,
                        getTextureAtlas(1,0,32,32),//source
                    {(float)x,(float)y,1,1},//dest
                    {0,0},//origin top left corner
                        0,//rotation
                        WHITE//tint
                        );
                    }

                    else if (downBlock->type == Block::woodLog && rightBlock->type == Block::leaves)
                    {
                        DrawTexturePro(
                     assetManager.woodLog,
                     getTextureAtlas(2,0,32,32),//source
                 {(float)x,(float)y,1,1},//dest
                 {0,0},//origin top left corner
                      0,//rotation
                     WHITE//tint
                      );
                    }

                    else if (downBlock->type == Block::woodLog && leftBlock->type == Block::leaves)
                    {
                        DrawTexturePro(
                     assetManager.woodLog,
                     getTextureAtlas(3,0,32,32),//source
                 {(float)x,(float)y,1,1},//dest
                 {0,0},//origin top left corner
                      0,//rotation
                     WHITE//tint
                      );
                    }

                    else if (downBlock->type == Block::woodLog && upBlock->type != Block::leaves)
                    {
                        DrawTexturePro(
                        assetManager.woodLog,
                        getTextureAtlas(6,0,32,32),//source
                    {(float)x,(float)y,1,1},//dest
                    {0,0},//origin top left corner
                        0,//rotation
                        WHITE//tint
                        );
                    }
                    else if (downBlock->type == Block::woodLog)
                    {
                        DrawTexturePro(
                       assetManager.woodLog,
                       getTextureAtlas(0,0,32,32),//source
                   {(float)x,(float)y,1,1},//dest
                   {0,0},//origin top left corner
                        0,//rotation
                       WHITE//tint
                        );
                    }else if (downBlock->type != Block::woodLog)
                    {
                        DrawTexturePro(
                        assetManager.woodLog,
                        getTextureAtlas(4,0,32,32),//source
                    {(float)x,(float)y,1,1},//dest
                    {0,0},//origin top left corner
                         0,//rotation
                        WHITE//tint
                         );
                    }
}
