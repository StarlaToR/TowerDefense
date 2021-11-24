#include "tiles.hpp"

Direction getNextDirection(char tilePos, Direction dir)
{
    if (tilePos == ROAD_STRAIGHT_EASTWEST || tilePos == ROAD_STRAIGHT_NORTHSOUTH || tilePos == ROAD_FOURWAY)
    {
        return dir;
    }
    else if (tilePos >= ROAD_TURN_NORTHEAST && tilePos <= ROAD_TURN_WESTNORTH)
    {
        return dir.dir == tilePos-ROAD_TURN_NORTHEAST ? dir.getLeft() : dir.getRight();
    }
    else if (tilePos >= ROAD_THREEWAY_NORTH && tilePos <= ROAD_THREEWAY_WEST)
    {
        if (dir.dir == tilePos-ROAD_THREEWAY_NORTH)
        {
            return GetRandomValue(0,1) ? dir.getLeft() : dir.getRight();
        }
        return dir;
    }
    else if (tilePos == ROAD_FOURWAY_TURN_RIGHT)
    {
        return dir.dir%2 == 0 ? dir.getRight() : dir.getLeft();
    }
    else if (tilePos == ROAD_FOURWAY_TURN_LEFT)
    {
        return dir.dir%2 == 0 ? dir.getLeft() : dir.getRight();
    }
    else if (tilePos >= ROAD_THREEWAY_FORCE_NORTH && tilePos <= ROAD_THREEWAY_FORCE_WEST)
    {
        return Direction(tilePos-ROAD_THREEWAY_FORCE_NORTH);
    }
    else
    {
        return dir;
    }
}