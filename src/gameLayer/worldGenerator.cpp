//
// Created by ddcha on 4/6/2026.
//

#include "worldGenerator.h"
#include <randomstuff.h>



void generateWorld(GameMap &gameMap, int seed)
{
    const int w = 900;
    const int h = 500;


    gameMap.create(w,h);

    int stoneHeight = 120;
    int dirtHeight = 50;

    std::ranlux24_base rng(seed);

    int dirtDirection = getRandomInt(rng,-2,2);
    int keepDirtDirectionTime = getRandomInt(rng,10,50);

    int stoneDirection = getRandomInt(rng,2,-2);
    int keepStoneDirectionTime = getRandomInt(rng,10,50);

    for (int x = 0;x < w; x++)
    {
        keepDirtDirectionTime--;
        //how many blocks i move before picking new direction
        if (keepDirtDirectionTime <= 0)
        {
            dirtDirection = getRandomInt(rng,-2,2);
            keepDirtDirectionTime = getRandomInt(rng,5,20);
        }

        switch (dirtDirection)
        {
            case -1:
                if (getRandomChance(rng,.2))
                {
                    dirtHeight--;
                    break;
                }
            case-2:
                if (getRandomChance(rng,.2))
                {
                    dirtHeight--;
                    break;
                }
                if (getRandomChance(rng,.2))
                {
                    dirtHeight--;
                    break;
                }
            case 1:
                if (getRandomChance(rng,.2))
                {
                    dirtHeight++;
                    break;
                }
            case 2:
                if (getRandomChance(rng,.2))
                {
                    dirtHeight++;
                }
                if (getRandomChance(rng,.2))
                {
                    dirtHeight++;
                    break;
                }
            default: ;
        }

        if (dirtHeight < 50)
            dirtHeight = 50;
        if (dirtHeight > 90)
            dirtHeight = 90;
        keepStoneDirectionTime--;
        //how many blocks i move before picking new direction
        if (keepStoneDirectionTime <= 0)
        {
            stoneDirection = getRandomInt(rng,-2,2);
            keepStoneDirectionTime = getRandomInt(rng,5,20);
        }

        switch (stoneDirection)
        {
            case -1:
                if (getRandomChance(rng,.2))
                {
                    stoneHeight--;
                    break;
                }
            case -2:
                if (getRandomChance(rng,.2))
                {
                    stoneHeight--;
                    break;
                }
                if (getRandomChance(rng,.2))
                {
                    stoneHeight--;
                    break;
                }
            case 1:
                if (getRandomChance(rng,.2))
                {
                    stoneHeight++;
                    break;
                }
            case 2:
                if (getRandomChance(rng,.2))
                {
                    stoneHeight++;
                }
                if (getRandomChance(rng,.2))
                {
                    stoneHeight++;
                    break;
                }
            default: ;
        }
        //make band for stone to spawn in
        if (stoneHeight < 60)
            stoneHeight = 60;
        if (stoneHeight > 120)
            stoneHeight = 120;

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


