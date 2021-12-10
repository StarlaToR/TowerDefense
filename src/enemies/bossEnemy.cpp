#include "bossEnemy.hpp"

BossEnemy::BossEnemy(TileMap& t, int wave)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    level = 1;
    slowTimer = 0;
    maxHealth = 10000;
    health = maxHealth;
    reward = 100000;
    speed = 1;
    damage = 50;

    currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    currentDirection = t.getTileAt(currentTile)-ROAD_START_NORTH;
    targetDirection = dirToAngle(currentDirection.dir);
    rotation = targetDirection;
    targetPos = currentDirection.getFowardTile(currentTile) + Vec2D(0.5f, 0.5f);
    angularVelocity= 0.05*speed;
    distanceToCenter = 0.1;
}

BossEnemy::~BossEnemy()
{
}