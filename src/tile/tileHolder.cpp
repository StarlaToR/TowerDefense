#include "tileHolder.hpp"

TileHolders::TileHolders()
{
    holders.push_back(TileHolder(GRASS, false, Vec2D(0,0)));
    holders.push_back(TileHolder(SAND, false, Vec2D(1,0)));
    holders.push_back(TileHolder(ROAD_STRAIGHT_EASTWEST, false, Vec2D(0,2)));
    holders.push_back(TileHolder(START_EAST, true, Vec2D(1,2)));
    holders.push_back(TileHolder(END_EAST, true, Vec2D(2,2)));
    holders.push_back(TileHolder(TUNNEL_EAST, true, Vec2D(0,3)));
    holders.push_back(TileHolder(DECO_TREE, true, Vec2D(0,5)));
    holders.push_back(TileHolder(DECO_BUSH, true, Vec2D(1,5)));
    holders.push_back(TileHolder(DECO_OIL, true, Vec2D(2,5)));
    holders.push_back(TileHolder(DECO_BARREL, true, Vec2D(0,6)));
    holders.push_back(TileHolder(DECO_SPIKES, true, Vec2D(1,6)));
    holders.push_back(TileHolder(DECO_WOOD, true, Vec2D(2,6)));
}

char getTileEquivalent(char tileIn)
{
    if (tileIn == GRASS || tileIn == GRASS_ALT) return GRASS;
    if (tileIn == SAND || tileIn == SAND_ALT) return SAND;
    if (tileIn <= ROAD_END_WEST) return ROAD_STRAIGHT_EASTWEST;
    if (tileIn <= DECO_TREE_ALT) return DECO_TREE;
    if (tileIn <= DECO_BUSH_ALT) return DECO_BUSH;
    if (tileIn == DECO_OIL) return DECO_OIL;
    if (tileIn <= DECO_BARREL_ALT) return DECO_BARREL;
    if (tileIn <= DECO_SPIKES_ALT) return DECO_SPIKES;
    if (tileIn <= DECO_WOOD_ALT) return DECO_WOOD;
    if (tileIn <= START_WEST) return START_EAST;
    if (tileIn <= END_WEST) return END_EAST;
    return UNDEFINED;
}