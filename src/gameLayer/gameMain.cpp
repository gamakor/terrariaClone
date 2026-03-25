//
// Created by ddcha on 3/24/2026.
//

#include "gameMain.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <raylib.h>

bool initGame()
{
    return true;
}

bool updateGame()
{
    Color c;
    c.r = 255;
    c.g = 0;
    c.b = 255;
    c.a = 255;

    DrawText("First Window Complete",(1280/2),(720/2),36,c);

    return true;
}

void closeGame()
{
    std::cout << "Game Closed! \n";
    std::ofstream f(RESOURCES_PATH "f.txt");
    f << "\nClosed\n";
    f.close();
}
