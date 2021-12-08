#pragma once
#include "enemy.hpp"

class ClassicEnemy: public Enemy
{
public:
    ClassicEnemy(TileMap* t, int wave);

    ClassicEnemy() {};

    int getTexture() override {return 121;}
    ~ClassicEnemy();
};
