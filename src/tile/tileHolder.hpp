#pragma once

#include "tiles.hpp"

class TileHolder
{
    public:
        TileID tile;
        bool isDeco;
        Vec2D position;
        TileHolder() : tile(GRASS) {}
        TileHolder(TileID id, bool deco, Vec2D pos) : tile(id), isDeco(deco), position(pos) {}

        unsigned char getTile() {return tile;}
};

class TileHolders {
    public:
        std::vector<TileHolder> holders = std::vector<TileHolder>();

        TileHolders();
};

char getTileEquivalent(char tileIn);