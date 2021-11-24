#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower()
    {
        damage = 1;
        range = 100;
        health = 100;
        maxHealth = 100;
        attackSpeed = 50;
    }

    void update();
    void getTexture();
    void attack(int damageDealt);
};