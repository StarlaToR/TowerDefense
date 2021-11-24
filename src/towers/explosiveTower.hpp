#include "tower.hpp"

class ExplosiveTower : public Tower
{
public:
    ExplosiveTower()
    {
        damage = 10;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 50;
        attackCooldown = 50;
        cost = 20;
    }

    void update();
    void getTexture();
};