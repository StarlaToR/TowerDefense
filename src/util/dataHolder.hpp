#pragma once

#include <raylib.h>
#include <cstddef>
#include "../tile/tileMap.hpp"
#include "../tile/tiles.hpp"

class DataHolder
{
public:
    const int screenWidth  = 1600;
    const int screenHeight = 900;
    int gameState = 0;
    size_t framecounter = 0;
    Texture2D logo;
    Texture2D tileTexture;
    Texture2D background;
    Texture2D button;
    Texture2D title;
    Texture2D logoIsart;
    TileMap map;
    Tiles tiles = Tiles();

    DataHolder() {}
    ~DataHolder() {}
    void unloadDatas();
    void handleGameState();
};