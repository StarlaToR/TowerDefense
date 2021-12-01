#include "healerEnenmy.hpp"

HealerEnemy::HealerEnemy(TileMap* t)
{
    position = t->startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    maxHealth = 20;
    health = 20;
    reward = 5;
    rotation = 0;
    speed = 3;
    damage = 1;

    currentDirection.dir = RIGHT;
    currentTile = Vec2D((int)t->startPos.x,(int)t->startPos.y);
    targetDirection = 0;
    targetPos = currentTile + Vec2D(1.5f,0.5f);
    angularVelocity= 0.15;
    distanceToCenter = 0.1;
}
