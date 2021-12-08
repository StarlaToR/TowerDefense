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
        tilesWithTower[i] = false;
    }
}

TileMap::TileMap(Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        tilesWithTower[i] = false;
        firstLayer[i] = GRASS;
        secondLayer[i] = UNDEFINED;
    }
}

TileMap::TileMap(const unsigned char* in, const unsigned char* in2, Vec2D start, Vec2D end) : startPos(start), endPos(end)
{
    for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++)
    {
        firstLayer[i] = in[i];
        secondLayer[i] = in2[i];
        tilesWithTower[i] = false;
    }
}

unsigned char TileMap::getTileAt(Vec2D pos, bool layer)
{
    if (pos.x >= getWidth() || pos.x < 0 || pos.y >= getHeight() || pos.y < 0) {
        return -1;
    }
    int index = (int)(pos.y)*getWidth()+(int)(pos.x);
    return layer ? secondLayer[index] : firstLayer[index];
}

void TileMap::setTileAt(Vec2D pos, unsigned char tile, bool layer)
{
    if (pos.x >= getWidth() || pos.x < 0 || pos.y >= getHeight() || pos.y < 0) {
        return;
    }
    int index = (int)(pos.y)*getWidth()+(int)(pos.x);
    (layer ? secondLayer[index] : firstLayer[index]) = tile;
}

void TileMap::setTileAndUpdate(Vec2D pos, unsigned char tile)
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
    setTileAt(pos,UNDEFINED,true);
    bool tmp = result & (1 << direction.dir);
    result = getTileConnexions(getTileAt(direction.getFowardTile(pos)));
    result = result ^ (1 << direction.getOpposite().dir);
    bool tmp2 = result & (1 << direction.getOpposite().dir);
    setTileAt(direction.getFowardTile(pos),getTileRoadByConnexion(result));
    setTileAt(direction.getFowardTile(pos),UNDEFINED,true);
    if (tmp != tmp2)
    {
        result = getTileConnexions(getTileAt(pos));
        result = result ^ (1 << direction.dir);
        setTileAt(pos,getTileRoadByConnexion(result));
    }
}

void TileMap::setAltTile(Vec2D pos)
{
    if (getTileAt(pos,true) != UNDEFINED)
    {
        char tileD = getTileAt(pos, true);
        if (tileD == DECO_TREE) setTileAt(pos,DECO_TREE_ALT, true);
        if (tileD == DECO_TREE_ALT) setTileAt(pos,DECO_TREE, true);
        if (tileD == DECO_WOOD) setTileAt(pos,DECO_WOOD_ALT, true);
        if (tileD == DECO_WOOD_ALT) setTileAt(pos,DECO_WOOD, true);
        if (tileD == DECO_BUSH) setTileAt(pos,DECO_BUSH_ALT, true);
        if (tileD == DECO_BUSH_ALT) setTileAt(pos,DECO_BUSH, true);
        if (tileD == DECO_BARREL) setTileAt(pos,DECO_BARREL_ALT, true);
        if (tileD == DECO_BARREL_ALT) setTileAt(pos,DECO_BARREL, true);
        if (tileD == DECO_SPIKES) setTileAt(pos,DECO_SPIKES_ALT, true);
        if (tileD == DECO_SPIKES_ALT) setTileAt(pos,DECO_SPIKES, true);
        return;
    }
    char tile = getTileAt(pos);
    if (tile == GRASS) setTileAt(pos,GRASS_ALT);
    if (tile == GRASS_ALT) setTileAt(pos,GRASS);
    if (tile == SAND) setTileAt(pos,SAND_ALT);
    if (tile == SAND_ALT) setTileAt(pos,SAND);
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
    if (isRoad(tile))
    {
        char result = 0;
        for (char i = LEFT; i >= UP; i--)
        {
            result = result << 1;
            result += isRoad(getTileAt(Direction(i).getFowardTile(pos)));
        }
        setTileAt(pos,getTileRoadByConnexion(result));
    }
}

bool TileMap::isRoad(unsigned char tile)
{
    return tile >= ROAD_STRAIGHT_EASTWEST && tile <= END_WEST;
}

bool TileMap::isValidStartEnd(unsigned char tile)
{
    return (tile >= ROAD_NORTH && tile <= ROAD_WEST);
}

unsigned char TileMap::getDefaultTile(unsigned char tile)
{
    if (!isRoad(tile)) return GRASS;
    if (tile >= ROAD_NORTH && tile <= ROAD_WEST) return tile;
    if (tile >= ROAD_START_NORTH && tile <= ROAD_START_WEST) return tile-4;
    if (tile >= ROAD_END_NORTH && tile <= ROAD_END_WEST) return tile-8;

    return ROAD_EAST;
}

bool TileMap::isTileWithTower(Vec2D pos)
{
    int tileId = pos.y * MAP_WIDTH + pos.x;
    return tilesWithTower[tileId];
}

void TileMap::setTileWithTower(Vec2D pos)
{
    int tileId = pos.y * MAP_WIDTH + pos.x;
    tilesWithTower[tileId] = true;
}

void TileMap::removeTowerFromTile(Vec2D pos)
{
    int tileId = pos.y * MAP_WIDTH + pos.x;
    tilesWithTower[tileId] = false;
}