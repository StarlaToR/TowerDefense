#pragma once

#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower()
    {
        damage = 2;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 15;
        attackCooldown = 0;
        cost = 5;
    }

    void attack(Enemy* e);
    int getTexture();
};