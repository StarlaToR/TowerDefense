#include "healerEnemy.hpp"

HealerEnemy::HealerEnemy(TileMap* t)
{
    position = t->startPos + Vec2D(0.5f,0.5f);
    slowTimer = 0;
    maxHealth = 20;
    health = 20;
    reward = 3;
    rotation = 0;
    speed = 3;
    damage = 1;
    range = 1.0f;
    healing = 5;
    healingCooldown = 0;

    currentDirection.dir = RIGHT;
    currentTile = Vec2D((int)t->startPos.x,(int)t->startPos.y);
    targetDirection = 0;
    targetPos = currentTile + Vec2D(1.5f,0.5f);
    angularVelocity= 0.15;
    distanceToCenter = 0.1;
}

void HealerEnemy::heal(std::forward_list<Enemy*>* enemies, Enemy* currentEnemy)
{
    bool healed = true;
    for (std::forward_list<Enemy*>::iterator i = enemies->begin(); i != enemies->end(); i++)
    {
        if((getPosition() - (*i)->getPosition()).getLength() <= range && (*i) != (currentEnemy))
        {
            (*i)->getHealed(healing);
            healed = false;
        }
    }
    if (healed)
    {
        getHealed(healing);
    }
    healingCooldown = 30;

}

bool HealerEnemy::update(TileMap* t, std::forward_list<Enemy*>* enemies)
{
    slowTimer = cut(slowTimer-1, 0, __INT_MAX__);
    healingCooldown = cut(healingCooldown-1, 0, __INT_MAX__);
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
    float vAng = slowTimer > 0 ? angularVelocity/4 : angularVelocity;
    float dec = cut(ang, -vAng, vAng);
    rotation = mod(rotation - dec, -PI, PI);
    if (ang > 1.6f/3.0f*PI || ang < -1.6f/3.0f*PI)
    {
        shouldStop = true;
    }
    if (!shouldStop)
    {
        this->position.x += this->speed / (slowTimer > 0 ? 240.0f : 60.0f) * cosf(rotation);
        this->position.y += this->speed / (slowTimer > 0 ? 240.0f : 60.0f) * sinf(rotation);
    }
    else
    {
        shouldStop = !(ang < vAng && ang > -vAng);
    }

    heal(enemies, this);

    return (health <= 0 || position.x < 0 || position.y < 0 || position.x >= t->getWidth() || position.y >= t->getHeight());
}