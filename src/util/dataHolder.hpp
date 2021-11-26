#pragma once

#include <raylib.h>
#include <cstddef>
#include "../tile/tileMap.hpp"

class DataHolder
{
public:
    const int screenWidth  = 1600;
    const int screenHeight = 900;
    int gameState = 0;
    size_t framecounter = 0;
    Texture2D logo;
    TileMap map;

    DataHolder() {}
    ~DataHolder() {}
    void unloadDatas();
    void handleGameState();
};