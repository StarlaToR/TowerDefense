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
    healing = 1;;
    healingCooldown = 30;

    currentDirection.dir = RIGHT;
    currentTile = Vec2D((int)t->startPos.x,(int)t->startPos.y);
    targetDirection = 0;
    targetPos = currentTile + Vec2D(1.5f,0.5f);
    angularVelocity= 0.15;
    distanceToCenter = 0.1;
}

void HealerEnemy::heal(std::forward_list<Enemy*>* enemies)
{
    for (std::forward_list<Enemy*>::iterator i = enemies->begin(); i != enemies->end(); i++)
    {
        if((getPosition() - (*i)->getPosition()).getLength() <= range)
        {
            (*i)->getHealed(healing);
        }
    }
}
