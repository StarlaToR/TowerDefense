#pragma once
#include "enemy.hpp"

class BossEnemy: public Enemy
{
public:
    BossEnemy(TileMap& t, int wave);

    BossEnemy() {};

    int getTexture() override {return TOWER_BASE;}
    ~BossEnemy();
};
