#pragma once
#include "tower.hpp"

class ExplosiveTower : public Tower
{
public:
    ExplosiveTower()
    {
        damage = 25;
        range = 30;
        health = 150;
        maxHealth = 150;
        attackSpeed = 30;
        attackCooldown = 30;
        cost = 50;
    }

    

    void update();
    int getTexture();
};