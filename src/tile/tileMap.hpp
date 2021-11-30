#pragma once

#include <new>

#include "../util/mathHelper.hpp"

#define MAP_WIDTH 24
#define MAP_HEIGHT 12

enum RenderType : char
{
    NORMAL = 0,
    EXTENDED,
    BORDER,
    DEBUG,
};

class TileMap
{
    public:
        Vec2D startPos;
        Vec2D endPos;

        char firstLayer[MAP_HEIGHT*MAP_WIDTH];
        char secondLayer[MAP_HEIGHT*MAP_WIDTH];

        TileMap();
        TileMap(Vec2D start, Vec2D end);
        TileMap(const char* in, const char* in2, Vec2D start, Vec2D end);
        ~TileMap() {}
        char getTileAt(Vec2D pos);
        void setTileAt(Vec2D pos, char tile);

        static int getWidth() {return MAP_WIDTH;}
        static int getHeight() {return MAP_HEIGHT;}
};