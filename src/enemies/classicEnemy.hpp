#pragma once
#include "enemy.hpp"

class ClassicEnemy: public Enemy
{
public:
    ClassicEnemy(TileMap& t)
    {
        this->position = t.startPos + Vec2D(0.5f,0.5f);
        this->slowTimer = 0;
        this->maxHealth = 20;
        this->health = 20;
        this->reward = 1;
        this->rotation = 0;
        this->speed = 2;
        this->currentDirection.dir = RIGHT;
        currentTile = Vec2D((int)t.startPos.x,(int)t.startPos.y);
        targetDirection = 0;
        targetPos = currentTile + Vec2D(1.5f,0.5f);
    }

    ClassicEnemy() {};

    void update(TileMap& t);
    void getDamage(int damageDealt) {}
    int getTexture() {return 0;}
};
