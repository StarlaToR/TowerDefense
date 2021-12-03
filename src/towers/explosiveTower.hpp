#pragma once
#include "tower.hpp"

class ExplosiveTower : public Tower
{
public:
    ExplosiveTower()
    {
        damage = 15;
        range = 70;
        health = 150;
        maxHealth = 150;
        attackSpeed = 20;
        attackCooldown = 20;
        cost = 20;
    }

    

    void update();
    int getTexture();
};