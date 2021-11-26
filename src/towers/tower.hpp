#pragma once
#include "../entities/entity.hpp"

class Tower: public Entity
{
protected:
    int range;
    int cost;
    int attackCooldown;
    int level;

public:
    void getDamage(int damageDealt)
    {
        health -= damageDealt;
    }
};