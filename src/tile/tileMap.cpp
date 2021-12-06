#include "tileMap.hpp"

char getTileRoadByConnexion(char connect)
{
    switch (connect)
        {
        case 0b0:
            return GRASS;
        case 0b1010:
            return ROAD_STRAIGHT_EASTWEST;
            break;
        case 0b101:
            return ROAD_STRAIGHT_NORTHSOUTH;
        case 0b11:
            return ROAD_TURN_NORTHEAST;
        case 0b110:
            return ROAD_TURN_EASTSOUTH;
        case 0b1100:
            return ROAD_TURN_SOUTHWEST;
        case 0b1001:
            return ROAD_TURN_WESTNORTH;
        case 0b111:
            return ROAD_THREEWAY_EAST;
        case 0b1110:
            return ROAD_THREEWAY_SOUTH;
        case 0b1101:
            return ROAD_THREEWAY_WEST;
        case 0b1011:
            return ROAD_THREEWAY_NORTH;
        case 0b10:
            return ROAD_EAST;
        case 0b1000:
            return ROAD_WEST;
        case 0b1:
            return ROAD_NORTH;
        case 0b100:
            return ROAD_SOUTH;
        default:
            return ROAD_FOURWAY;
        }
}

TileMap::TileMap() : startPos(Vec2D(0,6)), endPos(Vec2D(23,6))
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = GRASS;
        secondLayer[i] = UNDEFINED;
    }
}

TileMap::TileMap(Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = 0;
        secondLayer[i] = -1;
    }
}

TileMap::TileMap(const char* in, const char* in2, Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = in[i];
        secondLayer[i] = in2[i];
    }
}

char TileMap::getTileAt(Vec2D pos)
{
    if (pos.x+1 > getWidth() || pos.x < 0 || pos.y+1 > getHeight() || pos.y < 0) {
        return -1;
    }
    return firstLayer[(int)(pos.y)*getWidth()+(int)(pos.x)];
}

void TileMap::setTileAt(Vec2D pos, char tile)
{
    if (pos.x+1 > getWidth() || pos.x < 0 || pos.y+1 > getHeight() || pos.y < 0) {
        return;
    }
    firstLayer[(int)(pos.y)*getWidth()+(int)(pos.x)] = tile;
}

void TileMap::setTileAndUpdate(Vec2D pos, char tile)
{
    if (pos.x+1 > getWidth() || pos.x < 0 || pos.y+1 > getHeight() || pos.y < 0) {
        return;
    }
    firstLayer[(int)(pos.y)*getWidth()+(int)(pos.x)] = tile;
    updateTileAt(pos);
    for (char i = LEFT; i >= UP; i--)
        {
            updateTileAt(Direction(i).getFowardTile(pos));
        }
}

void TileMap::drawRoad(Vec2D pos, Direction direction)
{
    char result = getTileConnexions(getTileAt(pos));
    result = result ^ (1 << direction.dir);
    setTileAt(pos,getTileRoadByConnexion(result));
    result = getTileConnexions(getTileAt(direction.getFowardTile(pos)));
    result = result ^ (1 << direction.getOpposite().dir);
    setTileAt(direction.getFowardTile(pos),getTileRoadByConnexion(result));
}

void TileMap::setAltTile(Vec2D pos)
{
    char tile = getTileAt(pos);
    if (tile == GRASS || tile == SAND) setTileAt(pos,(tile+1) % 2);
    if (tile >= ROAD_FOURWAY && tile <= ROAD_FOURWAY_TURN_LEFT)
    {
        tile++;
        if (tile == ROAD_FOURWAY_TURN_LEFT+1) tile = ROAD_FOURWAY;
        setTileAt(pos,tile);
    }
    if (tile >= ROAD_THREEWAY_NORTH && tile <= ROAD_THREEWAY_WEST) setTileAt(pos,tile+7);
    if (tile >= ROAD_THREEWAY_FORCE_NORTH && tile <= ROAD_THREEWAY_FORCE_WEST) setTileAt(pos,tile-7);
}

void TileMap::updateTileAt(Vec2D pos)
{
    char tile = getTileAt(pos);
    if (isRoad(tile)) {
        char result = 0;
        for (char i = LEFT; i >= UP; i--)
        {
            result = result << 1;
            result += isRoad(getTileAt(Direction(i).getFowardTile(pos)));
        }
        setTileAt(pos,getTileRoadByConnexion(result));
    }
}

bool TileMap::isRoad(char tile)
{
    return tile >= ROAD_STRAIGHT_EASTWEST && tile <= ROAD_THREEWAY_FORCE_WEST;
}