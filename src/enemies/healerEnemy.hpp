#pragma once
#include "enemy.hpp"

class HealerEnemy: public Enemy
{
private:
    float range;
    int healing;
    int healingCooldown;
    void heal(std::list<Enemy*>& enemies, Enemy* currentEnemy, std::forward_list<Particle*>& particles);
public:
    HealerEnemy(TileMap& t, int wave, int difficulty);

    bool update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int& playerLife) override;
    int getTexture() override {return 52;}
};
