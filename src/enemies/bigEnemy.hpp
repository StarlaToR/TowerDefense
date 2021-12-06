#pragma once
#include "enemy.hpp"

class BigEnemy: public Enemy
{
public:
    BigEnemy(TileMap* t);

    BigEnemy() {};

    int getTexture() override {return 148;}
    ~BigEnemy();
};
