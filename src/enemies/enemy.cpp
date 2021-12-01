#include "enemy.hpp"

void Enemy::setSlowed(int value)
{
    this->slowTimer = value;
}

void Enemy::update(TileMap& t)
{
    Vec2D currentTilePosition((int)this->getPosition().x, (int)this->getPosition().y);
    if ((currentTilePosition.x != currentTile.x || currentTilePosition.y != currentTile.y) && (position-targetPos).lengthSquared() < 0.1) {
        
        currentTile = currentTilePosition;
        char newTile = t.getTileAt(currentTilePosition);
        
        currentDirection = getNextDirection(newTile, currentDirection);
        targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f,0.5f);
        
    }
    Vec2D dif = targetPos - position;
        float tmpDir;
        if (dif.x == 0)
            {
                if (dif.y > 0)
                    tmpDir = PI/2.0f;
                else
                    tmpDir = -PI/2.0f;
            }
        else
            {
                tmpDir = (atanf(dif.y / dif.x));
                if (dif.x < 0)
                {
                    tmpDir += PI;
                }
            }
        float dec = cut(mod(rotation - tmpDir, -PI, PI), -0.1, 0.1);
        rotation = mod(rotation - dec, -PI, PI);
    this->position.x += this->speed / 60.0f * cosf(rotation);
    this->position.y += this->speed / 60.0f * sinf(rotation);
}