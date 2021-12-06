#pragma once

#include "../util/direction.hpp"
#include <raylib.h>
#include <vector>

enum TileID : unsigned char
{
    GRASS = 0,
    SAND,
    GRASS_ALT,
    SAND_ALT,
    ROAD_STRAIGHT_EASTWEST,
    ROAD_STRAIGHT_NORTHSOUTH,
    ROAD_TURN_NORTHEAST,
    ROAD_TURN_EASTSOUTH,
    ROAD_TURN_SOUTHWEST,
    ROAD_TURN_WESTNORTH,
    ROAD_THREEWAY_NORTH,
    ROAD_THREEWAY_EAST,
    ROAD_THREEWAY_SOUTH,
    ROAD_THREEWAY_WEST,
    ROAD_FOURWAY,
    ROAD_FOURWAY_TURN_RIGHT,
    ROAD_FOURWAY_TURN_LEFT,
    ROAD_THREEWAY_FORCE_NORTH,
    ROAD_THREEWAY_FORCE_EAST,
    ROAD_THREEWAY_FORCE_SOUTH,
    ROAD_THREEWAY_FORCE_WEST,
    ROAD_NORTH,
    ROAD_EAST,
    ROAD_SOUTH,
    ROAD_WEST,
    ROAD_START_NORTH,
    ROAD_START_EAST,
    ROAD_START_SOUTH,
    ROAD_START_WEST,
    ROAD_END_NORTH,
    ROAD_END_EAST,
    ROAD_END_SOUTH,
    ROAD_END_WEST,
    DECO_TREE,
    DECO_TREE_ALT,
    DECO_BUSH,
    DECO_BUSH_ALT,
    DECO_OIL,
    DECO_BARREL,
    DECO_BARREL_ALT,
    DECO_SPIKES,
    DECO_SPIKES_ALT,
    DECO_WOOD,
    DECO_WOOD_ALT,
    START_NORTH,
    START_EAST,
    START_SOUTH,
    START_WEST,
    END_NORTH,
    END_EAST,
    END_SOUTH,
    END_WEST,
    TOWER_BASE = 154,
    UNDEFINED = 255,
};

class Tiles {
    public:
        std::vector<Rectangle> tileCrops = std::vector<Rectangle>();

        void registerTiles();
};

Direction getNextDirection(char tilePos, Direction dir);
char getTileConnexions(char tile);