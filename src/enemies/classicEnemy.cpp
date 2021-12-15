#include "classicEnemy.hpp"

ClassicEnemy::ClassicEnemy(TileMap& t, int wave, int difficulty)
{
    position = t.startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    level = wave/4+1;
    maxHealth = 10+5*level + 5 * difficulty;
    health = maxHealth;
    reward = 5 - difficulty;
    speed = 1+level;
    damage = 1;

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