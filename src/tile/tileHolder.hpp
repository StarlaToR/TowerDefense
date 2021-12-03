#include "tiles.hpp"

class TileHolder
{
    public:
        TileID tile;
        bool isDeco;
        TileHolder() : tile(GRASS) {}
        TileHolder(TileID id) : tile(id) {}

        char getTile() {return tile;}
};