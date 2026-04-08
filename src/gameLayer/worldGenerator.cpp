//
// Created by ddcha on 4/6/2026.
//

#include "worldGenerator.h"

#include <memory>
#include <randomstuff.h>
#include <FastNoiseLite.h>



void generateWorld(GameMap &gameMap, int seed)
{
    const int w = 900;
    const int h = 500;


    gameMap.create(w,h);

    int stoneHeight = 120;
    int dirtHeight = 50;

    std::ranlux24_base rng(seed++);

    std::unique_ptr<FastNoiseLite> dirtNoiseGenerator = std::make_unique<FastNoiseLite>();
    std::unique_ptr<FastNoiseLite> stoneNoiseGenerator = std::make_unique<FastNoiseLite>();

    dirtNoiseGenerator->SetSeed(seed++);
    stoneNoiseGenerator->SetSeed(seed++);

    dirtNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    dirtNoiseGenerator->SetFractalOctaves(1);
    dirtNoiseGenerator->SetFrequency(.02f);

    stoneNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    stoneNoiseGenerator->SetFractalOctaves(1);
    stoneNoiseGenerator->SetFrequency(.02f);


    //create a float array the size of w x h
    std::vector<float> dirtNoiseMap(w);
    std::vector<float> stoneNoiseMap(w);


    for (int x = 0; x < w; x++)
    {
        dirtNoiseMap[x] = dirtNoiseGenerator->GetNoise((float)x, 1.f);
        stoneNoiseMap[x] = stoneNoiseGenerator->GetNoise((float)x, 1.f);
    }
    //convert -1 to 1 to 0 to 1 timeStamp*/
    for (int i = 0; i < w; i++)
    {
        stoneNoiseMap[i] = (stoneNoiseMap[i] + 1) / 2;
        dirtNoiseMap[i] = (dirtNoiseMap[i] + 1) / 2;
    }

    //Not using while doing noise test
    /*int dirtDirection = getRandomInt(rng,-2,2);
    int keepDirtDirectionTime = getRandomInt(rng,10,50);

    int stoneDirection = getRandomInt(rng,2,-2);
    int keepStoneDirectionTime = getRandomInt(rng,10,50);*/

    int dirtOffsetStart = -5;
    int dirtOffsetEnd = 35;

    int stoneHeightStart = 80;
    int stoneHeightEnd = 170;

    for (int x = 0;x < w; x++)
    {
        int stoneHeight = stoneHeightStart + (stoneHeightEnd - stoneHeightStart) * stoneNoiseMap[x];
        int dirtHeight = dirtOffsetStart + (dirtOffsetEnd - dirtOffsetStart) * dirtNoiseMap[x];
        dirtHeight = stoneHeight - dirtHeight;

        for (int y = 0; y < h; y++)
        {

            Block b;

            if (y > dirtHeight)
            {
                b.type = Block::dirt;
            }
            if (y == dirtHeight)
            {
                b.type = Block::grassBlock;
            }
            if (y > stoneHeight)
            {
                b.type = Block::stone;
                if (getRandomChance(rng,0.01))
                {
                    b.type = Block::gold;
                }
            }

            gameMap.getBlockUnsafe(x,y) = b;
        }
    }
}


