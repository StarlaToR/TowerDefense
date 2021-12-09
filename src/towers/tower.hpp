#pragma once
#include "../entities/entity.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>
#include <list>
#include "../object/missile.hpp"

class Tower: public Entity
{
protected:
    int range;
    int cost;
    int attackCooldown;
    float angularVelocity;
    int textureID;

public:
    void getDamage(int damageDealt)
    {
        health -= damageDealt;
    }

    void update(std::list<Enemy*>* enemyIn, std::forward_list<Missile*>* missiles);
    virtual void attack(Enemy* e, std::forward_list<Missile*>* missiles) = 0;
    virtual void upgrade() = 0;
    Enemy* getNearestEnemy(std::list<Enemy*>* enemyIn);
    int getLevel();
    virtual const char* getName() = 0;

    virtual ~Tower() = 0;
};