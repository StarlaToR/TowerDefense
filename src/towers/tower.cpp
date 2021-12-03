#include "tower.hpp"

void Tower::update(DataHolder *t)
{
    Enemy *target = getNearestEnemy(t);
    
    if(target != nullptr)
    {
        Vec2D dif = target->getPosition() - position;
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
        rotation = tmpDir;
        attack(target);
    }
    if (attackCooldown > 0)
    {
        attackCooldown --;
    }
}

Enemy *Tower::getNearestEnemy(DataHolder *holder)
{
    Enemy *nearestEnemy = nullptr;
    float shortestDistance = 0;
    for (std::forward_list<Enemy *>::iterator i = holder->enemies.begin(); i != holder->enemies.end(); i++)
    {
        if (((*i)->getPosition() - position).getLength() <= range)
        {
            if (nearestEnemy == nullptr)
            {
                nearestEnemy = *i;
                shortestDistance = ((*i)->getPosition() - position).getLength();
            }
            else
            {
                if (shortestDistance > ((*i)->getPosition() - position).getLength())
                {
                    nearestEnemy = *i;
                    shortestDistance = ((*i)->getPosition() - position).getLength();
                }
            }
        }
    }

    return nearestEnemy;
}