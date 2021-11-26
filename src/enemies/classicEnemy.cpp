#include "classicEnemy.hpp"

void ClassicEnemy::update(TileMap& t)
{
    Vec2D currentTilePosition((int)this->getPosition().x, (int)this->getPosition().y % 1);
    char currentTile = t.getTileAt(currentTilePosition);

    int dir = angleToDir(this->rotation);
    
    Direction currentDirection(dir);
    Direction nextDirection = getNextDirection(currentTile, currentDirection);

    this->position.x += this->speed * cosf(rotation);
}