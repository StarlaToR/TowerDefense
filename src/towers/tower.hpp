#pragma once
#include "../entities/entity.hpp"
#include "../enemies/enemy.hpp"

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

    void update(TileMap* t);
    void attack(Enemy* e);
};