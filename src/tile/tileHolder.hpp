#include "tiles.hpp"

class TileHolder
{
    public:
        TileID tile;
        TileHolder() : tile(GRASS) {}
        TileHolder(TileID id) : tile(id) {}

        char getTexture() {return tile;}
};