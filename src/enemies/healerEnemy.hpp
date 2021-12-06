#pragma once
#include "enemy.hpp"
#include <forward_list>

class HealerEnemy: public Enemy
{
private:
    float range;
    int healing;
    int healingCooldown;
public:
    HealerEnemy(TileMap* t);
    HealerEnemy() {};

    bool update(TileMap* t, std::forward_list<Enemy*>* enemies);
    void heal(std::forward_list<Enemy*>* enemies, Enemy* currentEnemy);
    int getTexture() override {return 150;}
};
