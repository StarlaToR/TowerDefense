#include "classicTower.hpp"

ClassicTower::ClassicTower(Vec2D pos)
{
    position = pos+Vec2D(0.5f,0.5f);
    damage = 2;
    range = 50;
    health = 100;
    maxHealth = 100;
    attackSpeed = 15;
    attackCooldown = 0;
    cost = 5;
}

int ClassicTower::getTexture()
{
    return 60;
}

void ClassicTower::attack(Enemy* e)
{
    e->getDamage(damage);
    attackCooldown = attackSpeed;
}