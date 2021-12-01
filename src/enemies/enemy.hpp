#pragma once
#include "../entities/entity.hpp"
#include "../tile/tiles.hpp"

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
    float 
public:
    void setSlowed(int value);
    void update(TileMap& t);

};