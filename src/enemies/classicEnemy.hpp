#pragma once
#include "enemy.hpp"

class ClassicEnemy: public Enemy
{
public:
    ClassicEnemy(TileMap* t);

    ClassicEnemy() {};

    int getTexture() {return 0;}
};
