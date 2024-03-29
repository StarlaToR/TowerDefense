#pragma once
#include "enemy.hpp"

class BossEnemy: public Enemy
{
private:
    int anim = 120;
public:
    BossEnemy(TileMap& t, int wave, int difficulty);

    BossEnemy() {};

    int getTexture() override {return TOWER_BASE;}

    bool update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife) override;
    ~BossEnemy();
};
