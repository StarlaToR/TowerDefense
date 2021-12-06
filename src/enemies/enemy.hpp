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
    bool shouldStop;
public:
    void setSlowed(int value);
    bool update(TileMap* t);
    void getDamage(int damageDealt) {health = cut(health-damageDealt,0,maxHealth);}
    virtual ~Enemy() = 0;

};