#include "tower.hpp"

class SlowingTower : public Tower
{
public:
    SlowingTower()
    {
        damage = 1;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 10;
        attackCooldown = 10;
        cost = 15;
    }

    void update();
    void getTexture();
};