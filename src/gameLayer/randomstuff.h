//
// Created by ddcha on 4/3/2026.
//

#ifndef MYGAME_RANDOMSTUFF_H
#define MYGAME_RANDOMSTUFF_H
#pragma once
#include <random>

//returns float in range [min, max)
float getRandomFloat(std::ranlux24_base &rng,float min, float max);

//returns int in range [min, max)
int getRandomInt(std::ranlux24_base &rng,int min, int max);

bool getRandomChance(std::ranlux24_base &rng, float chance);

unsigned int hash2D(int x, int y);

int randomTile(int x, int y);


#endif //MYGAME_RANDOMSTUFF_H
