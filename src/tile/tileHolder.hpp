#pragma once

#include "tiles.hpp"

class TileHolder
{
    public:
        TileID tile;
        bool isDeco;
        TileHolder() : tile(GRASS) {}
        TileHolder(TileID id, bool deco) : tile(id), isDeco(deco) {}

        char getTile() {return tile;}
};

class TileHolders {
    public:
        std::vector<TileHolder> holders = std::vector<TileHolder>();

        TileHolders();
};

char getTileEquivalent(char tileIn);