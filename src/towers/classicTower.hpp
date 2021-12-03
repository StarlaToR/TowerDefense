#pragma once

#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower()
    {
        damage = 1;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 1;
        attackCooldown = 1;
        cost = 5;
    }


    int getTexture();
};