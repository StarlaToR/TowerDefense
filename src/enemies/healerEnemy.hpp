#pragma once
#include "enemy.hpp"

class HealerEnemy: public Enemy
{
public:
    HealerEnemy(TileMap* t);
    HealerEnemy() {};

    void heal();
    int getTexture() override {return 2;}
};
