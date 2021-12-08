#pragma once

#include <new>
#include <forward_list>
#include "../util/mathHelper.hpp"
#include "tiles.hpp"

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
        bool tilesWithTower[MAP_WIDTH* MAP_HEIGHT];
        unsigned char firstLayer[MAP_HEIGHT*MAP_WIDTH];
        unsigned char secondLayer[MAP_HEIGHT*MAP_WIDTH];

        TileMap();
        TileMap(Vec2D start, Vec2D end);
        TileMap(const unsigned char* in, const unsigned char* in2, Vec2D start, Vec2D end);
        ~TileMap() {}
        unsigned char getTileAt(Vec2D pos, bool layer = false);
        void setTileAt(Vec2D pos, unsigned char tile, bool layer = false);
        void setTileAndUpdate(Vec2D pos, unsigned char tile);
        void drawRoad(Vec2D pos, Direction direction);
        void setAltTile(Vec2D pos);
        void updateTileAt(Vec2D pos);
        bool isRoad(unsigned char tile);
        unsigned char getDefaultTile(unsigned char tile);
        bool isValidStartEnd(unsigned char tile);
        bool isTileWithTower(Vec2D pos);
        void setTileWithTower(Vec2D pos);
        void removeTowerFromTile(Vec2D pos);

        static int getWidth() {return MAP_WIDTH;}
        static int getHeight() {return MAP_HEIGHT;}
};