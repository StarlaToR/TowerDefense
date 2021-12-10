#pragma once
#include "enemy.hpp"

class BossEnemy: public Enemy
{
public:
    BossEnemy(TileMap& t, int wave);

    BossEnemy() {};

    int getTexture() override {return 154;}
    ~BossEnemy();
};
