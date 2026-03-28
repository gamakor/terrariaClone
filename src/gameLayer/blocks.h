//
// Created by ddcha on 3/28/2026.
//

#ifndef MYGAME_BLOCKS_H
#define MYGAME_BLOCKS_H
#pragma once

#include <cstdint>

struct Block
{
    enum
    {
        air = 0,
        dirt,
        grassBlock,
        stone,
        grass,
        sand,
        sandRuby,
        sandStone,
        woodPlank,
        stoneBricks,
        clay,
        woodLog,
        leaves,
        copper,
        iron,
        gold,
        copperBlock,
        ironBlock,
        goldBlock,
        bricks,
        snow,
        ice,
        rubyBlock,
        platform,
        workBench,
        glass,
        furnace,
        painting,
        sappling,
        snowBlueRuby,
        blueRubyBlock,
        door,
        jar,
        table,
        wardrobe,
        bookShelf,
        snowBricks,
        iceTable,
        iceWardrobe,
        iceBookShelf,
        icePlatform,
        sandTable,
        sandWardrobe,
        sandBookShelf,
        sandPlatform,
        woodenChest,
        iceChest,
        sandChest,
        boneChest,
        boneBricks,
        boneBench,
        boneWardrobe,
        boneBookShelf,
        bonePlatform,

        BLOCKS_COUNT,


    };

    std::uint16_t type = 0;
};

#endif //MYGAME_BLOCKS_H