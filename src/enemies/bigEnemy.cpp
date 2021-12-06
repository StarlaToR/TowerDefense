#include "bigEnemy.hpp"

BigEnemy::BigEnemy(TileMap* t)
{
    position = t->startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    maxHealth = 40;
    health = 40;
    reward = 5;
    rotation = 0;
    speed = 1;
    damage = 5;

    currentDirection.dir = RIGHT;
    currentTile = Vec2D((int)t->startPos.x,(int)t->startPos.y);
    targetDirection = 0;
    targetPos = currentTile + Vec2D(1.5f,0.5f);
    angularVelocity= 0.05;
    distanceToCenter = 0.1;
}

BigEnemy::~BigEnemy()
{
}