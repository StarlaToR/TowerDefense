#include "enemy.hpp"

void Enemy::setSlowed(int value)
{
    slowTimer = value;
}

bool Enemy::update(TileMap* t)
{
    Vec2D currentTilePosition((int)getPosition().x, (int)getPosition().y);
    if ((currentTilePosition.x != currentTile.x || currentTilePosition.y != currentTile.y) && (position - targetPos).lengthSquared() < distanceToCenter)
    {
        
        currentTile = currentTilePosition;
        char newTile = t->getTileAt(currentTilePosition);

        currentDirection = getNextDirection(newTile, currentDirection);
        targetPos = currentDirection.getFowardTile(currentTilePosition) + Vec2D(0.5f, 0.5f);
    }
    Vec2D dif = targetPos - position;
    float tmpDir;
    if (dif.x == 0)
    {
        if (dif.y > 0)
            tmpDir = PI / 2.0f;
        else
            tmpDir = -PI / 2.0f;
    }
    else
    {
        tmpDir = (atanf(dif.y / dif.x));
        if (dif.x < 0)
        {
            tmpDir += PI;
        }
    }
    float ang = mod(rotation - tmpDir, -PI, PI);
    float dec = cut(ang, -angularVelocity, angularVelocity);
    rotation = mod(rotation - dec, -PI, PI);
    if (ang > 1.6f/3.0f*PI || ang < -1.6f/3.0f*PI)
    {
        shouldStop = true;
    }
    if (!shouldStop)
    {
        this->position.x += this->speed / 60.0f * cosf(rotation);
        this->position.y += this->speed / 60.0f * sinf(rotation);
    }
    else
    {
        shouldStop = !(ang < angularVelocity && ang > -angularVelocity);
    }
    return (position.x < 0 || position.y < 0 || position.x >= t->getWidth() || position.y >= t->getHeight());
}

Enemy::~Enemy()
{
}