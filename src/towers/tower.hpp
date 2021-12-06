#pragma once
#include "../entities/entity.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>

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

    void update(std::forward_list<Enemy*>* enemyIn);
    virtual void attack(Enemy* e) = 0;
    Enemy* getNearestEnemy(std::forward_list<Enemy*>* enemyIn);
};