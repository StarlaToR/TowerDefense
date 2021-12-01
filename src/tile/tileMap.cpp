#include "tileMap.hpp"

TileMap::TileMap() : startPos(Vec2D(0,0)), endPos(Vec2D(23,6))
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = 0;
        secondLayer[i] = -1;
    }
}

TileMap::TileMap(Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = 0;
        secondLayer[i] = -1;
    }
}

TileMap::TileMap(const char* in, const char* in2, Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = in[i];
        secondLayer[i] = in2[i];
    }
}

char TileMap::getTileAt(Vec2D pos)
{
    if (pos.x+1 > getWidth() || pos.x < 0 || pos.y+1 > getHeight() || pos.y < 0) {
        return -1;
    }
    return firstLayer[(int)(pos.y)*getWidth()+(int)(pos.x)];
}

void TileMap::setTileAt(Vec2D pos, char tile)
{
    if (pos.x+1 > getWidth() || pos.x < 0 || pos.y+1 > getHeight() || pos.y < 0) {
        return;
    }
    firstLayer[(int)(pos.y)*getWidth()+(int)(pos.x)] = tile;
}