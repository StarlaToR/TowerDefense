#include "bigEnemy.hpp"

BigEnemy::BigEnemy(TileMap& t, int wave, int difficulty)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    level = wave/4+1;
    slowTimer = 0;
    maxHealth = 20+20*level + 20 * difficulty;
    health = maxHealth;
    reward = 6 - difficulty;
    speed = 1+level/2;
    damage = 5+level;

    currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    currentDirection = t.getTileAt(currentTile)-ROAD_START_NORTH;
    targetDirection = dirToAngle(currentDirection.dir);
    rotation = targetDirection;
    targetPos = currentDirection.getFowardTile(currentTile) + Vec2D(0.5f, 0.5f);
    angularVelocity= 0.05*speed;
    distanceToCenter = 0.1;
}

BigEnemy::~BigEnemy()
{
}