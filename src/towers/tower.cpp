#include "tower.hpp"

void Tower::update(std::list<Enemy*>& enemyIn, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles)
{
    Enemy *target = getNearestEnemy(enemyIn);
    
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
        float ang = mod(rotation - tmpDir, -PI, PI);
        float dec = cut(ang, -angularVelocity, angularVelocity);
        rotation = mod(rotation - dec, -PI, PI);
        if (attackCooldown <= 0 && ang == dec)
        {
            if (attack(target, missiles, particles) && towerSound != nullptr) PlaySound(*towerSound);
        }
    }

    if (attackCooldown > 0)
    {
        attackCooldown --;
    }
}

Enemy *Tower::getNearestEnemy(std::list<Enemy*>& enemyIn)
{
    Enemy *nearestEnemy = nullptr;
    float shortestDistance = 0;
    for (std::list<Enemy*>::iterator i = enemyIn.begin(); i != enemyIn.end(); i++)
    {
        if (!(*i)->isUnderGround() && ((*i)->getPosition() - position).getLength() <= range)
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

int Tower::getLevel()
{
    return level;
}

float Tower::getRange()
{
    return range;
}

int Tower::getCost()
{
    return cost;
}

void Tower::setCost(int a)
{
    cost = a;
}

void Tower::getDamage(int damageDealt)
{
    health -= damageDealt;
}


Tower::~Tower()
{
}