#include "classicEnemy.hpp"


ClassicEnemy::ClassicEnemy(TileMap* t, int wave)
{
    position = t->startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    level = wave/4;
    maxHealth = 20;
    health = 20;
    reward = 1;
    rotation = 0;
    speed = 2;
    damage = 3;

    currentDirection.dir = RIGHT;
    currentTile = Vec2D((int)t->startPos.x,(int)t->startPos.y);
    targetDirection = 0;
    targetPos = currentTile + Vec2D(1.5f,0.5f);
    angularVelocity= 0.1;
    distanceToCenter = 0.1;
}