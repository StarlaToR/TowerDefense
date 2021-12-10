#include "classicEnemy.hpp"

ClassicEnemy::ClassicEnemy(TileMap& t, int wave)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    level = wave/4+1;
    maxHealth = 10+10*level;
    health = maxHealth;
    reward = 10*level;
    speed = 1+level;
    damage = 2+level;

    currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    currentDirection = t.getTileAt(currentTile)-ROAD_START_NORTH;
    targetDirection = dirToAngle(currentDirection.dir);
    rotation = targetDirection;
    targetPos = currentDirection.getFowardTile(currentTile) + Vec2D(0.5f, 0.5f);
    angularVelocity= 0.05*speed;
    distanceToCenter = 0.1;
}

ClassicEnemy::~ClassicEnemy()
{
}