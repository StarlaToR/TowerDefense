#pragma once
#include "../object/object.hpp"

class Entity : public Object
{
protected:
    int health;
    int maxHealth;
    int damage;
    int attackSpeed;
public:
    
    virtual void getDamage(int damageDealt) = 0;
    virtual void update() = 0;
    virtual void getTexture() = 0;
};