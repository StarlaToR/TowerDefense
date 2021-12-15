#pragma once
#include "enemy.hpp"

class BigEnemy: public Enemy
{
public:
    BigEnemy(TileMap& t, int wave, int difficulty);

    BigEnemy() {};

    int getTexture() override {return 129;}
    ~BigEnemy();
};
