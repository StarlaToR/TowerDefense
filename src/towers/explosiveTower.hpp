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
        attackSpeed = 90;
        attackCooldown = 0;
        cost = 20;
    }

    
    void attack(Enemy* e);
    int getTexture();
};