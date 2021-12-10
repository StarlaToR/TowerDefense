#pragma once
#include "enemy.hpp"

class BigEnemy: public Enemy
{
public:
    BigEnemy(TileMap& t, int wave);

    BigEnemy() {};

    int getTexture() override {return 129;}
    ~BigEnemy();
};
