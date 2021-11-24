#include "tower.hpp"

class Classic : public Tower
{
public:
    Classic()
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