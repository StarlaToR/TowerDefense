#pragma once
#include "enemy.hpp"

class BigEnemy: public Enemy
{
public:
    BigEnemy(TileMap& t)
    {
        this->position = t.startPos + Vec2D(0.5f,0.5f);
        this->slowTimer = 0;
        this->maxHealth = 40;
        this->health = 40;
        this->reward = 5;
        this->rotation = 0;
        this->speed = 1;
        this->currentDirection.dir = RIGHT;
        currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    }

    BigEnemy() {};

    void update(TileMap& t);
    void getDamage(int damageDealt) {}
    int getTexture() {return 0;}
};
