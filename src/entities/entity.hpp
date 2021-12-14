#pragma once
#include "../object/object.hpp"

class Entity : public Object
{
protected:
    int health;
    int maxHealth;
    int attackSpeed;
    int level;
public:
    
    virtual void getDamage(int damageDealt) = 0;
    virtual int getTexture() = 0;
    float getHealth();
    virtual unsigned int getColor();
};