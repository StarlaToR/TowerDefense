#pragma once
#include "enemy.hpp"

class BossEnemy: public Enemy
{
public:
    BossEnemy(TileMap& t, int wave);

    BossEnemy() {};

    int getTexture() override {return TOWER_BASE;}

    bool update(TileMap& t, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife) override;
    ~BossEnemy();
};
