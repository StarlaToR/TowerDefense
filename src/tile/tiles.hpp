#pragma once

#include "../util/direction.hpp"
#include <raylib.h>
#include <vector>

enum TileID : char
{
    GRASS = 0,
    SAND,
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
    START_NORTH,
    START_EAST,
    START_SOUTH,
    START_WEST,
    END_NORTH,
    END_EAST,
    END_SOUTH,
    END_WEST,
};

class Tiles {
    public:
        std::vector<Rectangle> tileCrops = std::vector<Rectangle>();

        void registerTiles();
};

Direction getNextDirection(char tilePos, Direction dir);
char getTileConnexions(char tile);