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
    bool shouldStop = false;
public:
    void setSlowed(int value);
    bool update(TileMap* t, std::forward_list<Enemy*>* enemies);
    void getDamage(int damageDealt) {health = cut(health-damageDealt,0,maxHealth);}
    void getHealed(int heal);
    int getReward();
    virtual ~Enemy() = 0;
};