#include "tower.hpp"

class SlowingTower : public Tower
{
private:
    int slowingTime = 120;
public:
    SlowingTower()
    {
        damage = 1;
        range = 50;
        health = 100;
        maxHealth = 100;
        attackSpeed = 60;
        attackCooldown = 0;
        cost = 10;
    }

    void attack(Enemy* e);
    int getTexture();
};