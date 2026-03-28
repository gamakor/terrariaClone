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
        air=0,
        dirt,

        BLOCK_COUNT,

    };

    std::uint16_t type = 0;
};

#endif //MYGAME_BLOCKS_H