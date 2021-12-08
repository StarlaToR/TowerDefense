#include "slowingTower.hpp"

SlowingTower::SlowingTower(Vec2D pos)
{
    damage = 1;
    range = 5;
    health = 100;
    maxHealth = 100;
    attackSpeed = 60;
    attackCooldown = 0;
    cost = 10;
    position = pos+Vec2D(0.5f,0.5f);
    rotation = 0;
    angularVelocity = 0.07f;
    level = 1;
    slowingTime = 120;
    textureID = 61;
}


void SlowingTower::attack(Enemy* e,std::forward_list<Missile*>* missiles)
{
    e->getDamage(damage);
    e->setSlowed(slowingTime);
    attackCooldown = attackSpeed;
}

int SlowingTower::getTexture()
{
    return textureID;
}

void SlowingTower::upgrade()
{
    if(level < 4)
    {
        level += 1;
        slowingTime += 30;
        attackSpeed -= 10;
        textureID += 11;
    }
}