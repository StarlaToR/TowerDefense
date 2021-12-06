#include "slowingTower.hpp"

SlowingTower::SlowingTower(Vec2D pos)
{
    damage = 1;
    range = 2;
    health = 100;
    maxHealth = 100;
    attackSpeed = 60;
    attackCooldown = 0;
    cost = 10;
    position = pos;
    rotation = 0;
}


void SlowingTower::attack(Enemy* e,std::forward_list<Missile*> missiles)
{
    e->getDamage(damage);
    e->setSlowed(slowingTime);
    attackCooldown = attackSpeed;
}

int SlowingTower::getTexture()
{
    return 61;
}