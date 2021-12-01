#pragma once
#include "enemy.hpp"

class HealerEnemy: public Enemy
{
public:
    HealerEnemy(TileMap& t)
    {
        this->position = t.startPos + Vec2D(0.5f,0.5f);
        this->slowTimer = 0;
        this->maxHealth = 20;
        this->health = 20;
        this->reward = 5;
        this->rotation = 0;
        this->speed = 1;
        this->currentDirection.dir = RIGHT;
        currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
    }

    HealerEnemy() {};

    void update(TileMap& t);
    void getDamage(int damageDealt) {}
    int getTexture() {return 0;}
};
