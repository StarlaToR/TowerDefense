#pragma once

#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower()
    {
        damage = 5;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 25;
        attackCooldown = 25;
        cost = 10;
    }

    void update();
    int getTexture();
};