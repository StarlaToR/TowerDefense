#include "tileMap.hpp"

TileMap::TileMap() : startPos(Vec2D()), endPos(Vec2D())
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = 0;
        secondLayer[i] = 0;
    }
}

TileMap::TileMap(const char* in, Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = in[i];
        secondLayer[i] = in[i];
    }
}