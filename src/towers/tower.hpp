#pragma once
#include "../entities/entity.hpp"
#include "../enemies/enemy.hpp"
#include "../util/dataHolder.hpp"

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

    void update(DataHolder* t);
    void attack(Enemy* e);
    Enemy* getNearestEnemy(DataHolder* t);
};