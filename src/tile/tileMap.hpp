#pragma once

#include <new>
#include "../util/mathHelper.hpp"

#define MAP_WIDTH 24
#define MAP_HEIGHT 12

class TileMap
{
    public:
        Vec2D startPos;
        Vec2D endPos;

        char firstLayer[MAP_HEIGHT*MAP_WIDTH];
        char secondLayer[MAP_HEIGHT*MAP_WIDTH];

        TileMap();
        TileMap(const char* in, Vec2D start, Vec2D end);
        ~TileMap() {}
        char getTileAt(Vec2D pos);
        void setTileAt(Vec2D pos, char tile);
};