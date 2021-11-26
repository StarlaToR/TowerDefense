#pragma once
#include "enemy.hpp"
#include "../tile/tileMap.hpp"

class ClassicEnemy: public Enemy
{
public:
    ClassicEnemy(TileMap& t)
    {
        this->position = t.startPos;
        this->slowTimer = 0;
        this->maxHealth = 20;
        this->health = 20;
        this->reward = 1;
        this->rotation = 0;
        this->speed = 2;
        this->currentDirection.dir = RIGHT;
    }

    void update(TileMap& t);
};
