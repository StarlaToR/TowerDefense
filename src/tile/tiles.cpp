#include "tiles.hpp"

Direction getNextDirection(char tilePos, Direction dir)
{
    if (tilePos == ROAD_STRAIGHT_EASTWEST || tilePos == ROAD_STRAIGHT_NORTHSOUTH || tilePos == ROAD_FOURWAY)
    {
        return dir;
    }
    else if (tilePos >= ROAD_TURN_NORTHEAST && tilePos <= ROAD_TURN_WESTNORTH)
    {
        return dir.getOpposite().dir == tilePos-ROAD_TURN_NORTHEAST ? dir.getLeft() : dir.getRight();
    }
    else if (tilePos >= ROAD_THREEWAY_NORTH && tilePos <= ROAD_THREEWAY_WEST)
    {
        if (dir.getOpposite().dir == tilePos-ROAD_THREEWAY_NORTH)
        {
            return GetRandomValue(0,1) ? dir.getLeft() : dir.getRight();
        }
        return dir;
    }
    else if (tilePos == ROAD_FOURWAY_TURN_RIGHT)
    {
        return dir.dir%2 == 0 ? dir.getLeft() : dir.getRight();
    }
    else if (tilePos == ROAD_FOURWAY_TURN_LEFT)
    {
        return dir.dir%2 == 0 ? dir.getRight() : dir.getLeft();
    }
    else if (tilePos >= ROAD_THREEWAY_FORCE_NORTH && tilePos <= ROAD_THREEWAY_FORCE_WEST)
    {
        return Direction(tilePos-ROAD_THREEWAY_FORCE_NORTH);
    }
    else if (tilePos >= ROAD_NORTH && tilePos <= ROAD_WEST)
    {
        return Direction(tilePos-ROAD_NORTH);
    }
    else
    {
        return dir.getOpposite();
    }
}

char getTileConnexions(char tile)
{
    switch (tile)
    {
    case ROAD_STRAIGHT_EASTWEST :
        return 0b1010;
    case ROAD_STRAIGHT_NORTHSOUTH :
        return 0b0101;
    case ROAD_TURN_NORTHEAST :
        return 0b0011;
    case ROAD_TURN_EASTSOUTH :
        return 0b0110;
    case ROAD_TURN_SOUTHWEST :
        return 0b1100;
    case ROAD_TURN_WESTNORTH :
        return 0b1001;
    case ROAD_THREEWAY_NORTH :
    case ROAD_THREEWAY_FORCE_NORTH :
        return 0b1011;
    case ROAD_THREEWAY_EAST :
    case ROAD_THREEWAY_FORCE_EAST :
        return 0b0111;
    case ROAD_THREEWAY_SOUTH :
    case ROAD_THREEWAY_FORCE_SOUTH :
        return 0b1110;
    case ROAD_THREEWAY_WEST :
    case ROAD_THREEWAY_FORCE_WEST :
        return 0b1101;
    case ROAD_FOURWAY :
    case ROAD_FOURWAY_TURN_RIGHT :
    case ROAD_FOURWAY_TURN_LEFT :
        return 0b1111;
    case ROAD_NORTH:
        return 0b0001;
    case ROAD_EAST:
        return 0b0010;
    case ROAD_SOUTH:
        return 0b0100;
    case ROAD_WEST:
        return 0b1000;
    default:
        return 0;
    }
}

void Tiles::registerTiles()
{
    for (int i = 0; i < TOWER_BASE; i++)
    {
        tileCrops.push_back(Rectangle{ (float)(i%11*128), (float)(i/11*128), 128, 128});
    }
    tileCrops.push_back(Rectangle{ 0.0f, 0.0f, 128.0f, 128.0f});
}