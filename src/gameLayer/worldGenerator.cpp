//
// Created by ddcha on 4/6/2026.
//

#include "worldGenerator.h"
#include <FastNoiseLite.h>
#include <memory>
#include <randomstuff.h>
#include <helpers.h>



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
//Plains noise gen
    dirtNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    dirtNoiseGenerator->SetFractalOctaves(1);
    dirtNoiseGenerator->SetFrequency(.0019f);

    stoneNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    stoneNoiseGenerator->SetFractalOctaves(1);
    stoneNoiseGenerator->SetFrequency(.0019f);


    //create a float array the size of w for plains
    std::vector<float> dirtPlainNoiseMap(w);
    std::vector<float> stonePlainNoiseMap(w);


    for (int x = 0; x < w; x++)
    {
        dirtPlainNoiseMap[x] = dirtNoiseGenerator->GetNoise((float)x, 1.f);
        stonePlainNoiseMap[x] = stoneNoiseGenerator->GetNoise((float)x, 1.f);
    }
    //convert -1 to 1 to 0 to 1 timeStamp*/
    for (int i = 0; i < w; i++)
    {
        stonePlainNoiseMap[i] = (stonePlainNoiseMap[i] + 1) / 2;
        dirtPlainNoiseMap[i] = (dirtPlainNoiseMap[i] + 1) / 2;
    }


    //create noise maps for mountains
    dirtNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    dirtNoiseGenerator->SetFractalOctaves(1);
    dirtNoiseGenerator->SetFrequency(.01f);

    stoneNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_Perlin);
    stoneNoiseGenerator->SetFractalOctaves(1);
    stoneNoiseGenerator->SetFrequency(.01f);

    std::vector<float> dirtMountainNoiseMap(w);
    std::vector<float> stoneMountainNoiseMap(w);

    for (int x = 0; x < w; x++)
    {
        dirtMountainNoiseMap[x] = dirtNoiseGenerator->GetNoise((float)x, 1.f);
        stoneMountainNoiseMap[x] = stoneNoiseGenerator->GetNoise((float)x, 1.f);
    }
    //convert -1 to 1 to 0 to 1 timeStamp*/
    for (int i = 0; i < w; i++)
    {
        stoneMountainNoiseMap[i] = (stoneMountainNoiseMap[i] + 1) / 2;
        dirtMountainNoiseMap[i] = (dirtMountainNoiseMap[i] + 1) / 2;
    }



    //create noise maps for lerp values
    dirtNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    dirtNoiseGenerator->SetFractalOctaves(2);
    dirtNoiseGenerator->SetFrequency(.003f);

    stoneNoiseGenerator->SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
    stoneNoiseGenerator->SetFractalOctaves(1);
    stoneNoiseGenerator->SetFrequency(.003f);


    //holds result of lerp
    dirtEndResultNoiseMap.resize(w);
    stoneEndResultNoiseMap.resize(w);

    for (int x = 0; x < w; x++)
    {
        dirtEndResultNoiseMap[x] = dirtNoiseGenerator->GetNoise((float)x, 1.f);
        stoneEndResultNoiseMap[x] = stoneNoiseGenerator->GetNoise((float)x, 1.f);
    }

    //convert -1 to 1 to 0 to 1 timeStamp*/
    for (int i = 0; i < w; i++)
    {
        dirtEndResultNoiseMap[i] = (dirtEndResultNoiseMap[i] + 1) / 2;
        stoneEndResultNoiseMap[i] = (stoneEndResultNoiseMap[i] + 1) / 2;
    }


    //combine mountain and plains
    for (int x = 0; x < w; x++)
    {
        dirtEndResultNoiseMap[x] = lerp(dirtEndResultNoiseMap[x],dirtMountainNoiseMap[x],dirtEndResultNoiseMap[x]);
        stoneEndResultNoiseMap[x] = lerp(stoneEndResultNoiseMap[x],stoneMountainNoiseMap[x],stoneEndResultNoiseMap[x]);
        dirtEndResultNoiseMap[x] = smoothstep(dirtEndResultNoiseMap[x]);
        stoneEndResultNoiseMap[x] = smoothstep(stoneEndResultNoiseMap[x]);
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
        int stoneHeight = stoneHeightStart + (stoneHeightEnd - stoneHeightStart) * dirtEndResultNoiseMap[x];
        int dirtHeight = dirtOffsetStart + (dirtOffsetEnd - dirtOffsetStart) * stoneEndResultNoiseMap[x];
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

float getNoise(int blockType,int x)
{
    if (blockType == Block::dirt)
    {
        return dirtEndResultNoiseMap[x];
    }
    else if (blockType == Block::stone)
    {
        return stoneEndResultNoiseMap[x];
    }
    return 0;
}


