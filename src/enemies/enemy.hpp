#pragma once
#include "../entities/entity.hpp"
#include "../tile/tileMap.hpp"

class Enemy : public Entity
{
protected:
    int speed;
    int reward;
    int slowTimer;
    Direction currentDirection;
    float targetDirection;
    Vec2D currentTile;
    Vec2D targetPos;
    float angularVelocity;
    float distanceToCenter;
public:
    void setSlowed(int value);
    bool update(TileMap* t);
    void getDamage(int damageDealt) {}
    virtual ~Enemy() = 0;

};