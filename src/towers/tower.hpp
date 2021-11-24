#pragma once
#include "../entities/entity.hpp"

class Tower: public Entity
{
protected:
    int range;
    int cost;
    int attackCooldown;
public:
    Tower()
    {

    }

    ~Tower()
    {

    }

    void getDamage(int damageDealt)
    {
        health -= damageDealt;
    }
};