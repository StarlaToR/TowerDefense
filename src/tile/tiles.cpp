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
    else
    {
        return dir;
    }
}

void Tiles::registerTiles() {
    tileCrops.push_back(Rectangle{ 384, 896, 128, 128});
    tileCrops.push_back(Rectangle{ 256, 128, 128, 128});
    tileCrops.push_back(Rectangle{ 0, 768, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 896, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 384, 128, 128});
    tileCrops.push_back(Rectangle{ 0, 640, 128, 128});
    tileCrops.push_back(Rectangle{ 0, 512, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 256, 128, 128});
    tileCrops.push_back(Rectangle{ 384, 384, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 768, 128, 128});
    tileCrops.push_back(Rectangle{ 384, 768, 128, 128});
    tileCrops.push_back(Rectangle{ 512, 512, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 640, 128, 128});
    tileCrops.push_back(Rectangle{ 384, 512, 128, 128});
    tileCrops.push_back(Rectangle{ 384, 512, -128, 128});
    tileCrops.push_back(Rectangle{ 384, 384, 128, 128});
    tileCrops.push_back(Rectangle{ 128, 768, 128, 128});
    tileCrops.push_back(Rectangle{ 384, 768, 128, 128});
    tileCrops.push_back(Rectangle{ 512, 512, 128, 128});
    
}