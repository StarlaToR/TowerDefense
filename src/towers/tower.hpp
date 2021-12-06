#pragma once
#include "../entities/entity.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>
#include "../object/missile.hpp"

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

    void update(std::forward_list<Enemy*>* enemyIn, std::forward_list<Missile*> missiles);
    virtual void attack(Enemy* e, std::forward_list<Missile*> missiles) = 0;
    Enemy* getNearestEnemy(std::forward_list<Enemy*>* enemyIn);
};