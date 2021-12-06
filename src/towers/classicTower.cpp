#include "classicTower.hpp"

ClassicTower::ClassicTower(Vec2D pos)
{
    position = pos+Vec2D(0.5f,0.5f);
    damage = 2;
    range = 3;
    health = 100;
    maxHealth = 100;
    attackSpeed = 15;
    attackCooldown = 0;
    cost = 5;
}

int ClassicTower::getTexture()
{
    return 121;
}

void ClassicTower::attack(Enemy* e,std::forward_list<Missile*> missiles)
{
    e->getDamage(damage);
    attackCooldown = attackSpeed;
}