#pragma once
#include "enemy.hpp"
#include <forward_list>

class HealerEnemy: public Enemy
{
private:
    float range;
    int healing;
    int healingCooldown;
    void heal(std::forward_list<Enemy*>* enemies, Enemy* currentEnemy, std::forward_list<Particle*>* particles);
public:
    HealerEnemy(TileMap* t);
    HealerEnemy() {};

    bool update(TileMap* t, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles) override;
    int getTexture() override {return 52;}
};
