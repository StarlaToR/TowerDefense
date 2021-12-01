#include "classicEnemy.hpp"

void ClassicEnemy::update(TileMap& t)
{
    Vec2D currentTilePosition((int)this->getPosition().x, (int)this->getPosition().y);
    if (currentTilePosition.x != currentTile.x || currentTilePosition.y != currentTile.y) {
        position = currentTilePosition + Vec2D(0.5f,0.5f);
        currentTile = currentTilePosition;
        char newTile = t.getTileAt(currentTilePosition);

        int dir = angleToDir(this->rotation);
        Direction currentDirection(dir);
        Direction nextDirection = getNextDirection(newTile, currentDirection);
        this->rotation = dirToAngle(nextDirection.dir);
    }

    this->position.x += this->speed / 60.0f * cosf(rotation);
    this->position.y += this->speed / 60.0f * sinf(rotation);
}