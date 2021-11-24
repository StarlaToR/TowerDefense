#pragma once
#include "../entities/entity.hpp"

class Enemy : public Entity
{
protected:
    int speed;
    int reward;
    int slowTimer;
public:
    void setSlowed(int value);
};