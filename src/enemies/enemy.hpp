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
public:
    void setSlowed(int value);
};