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
    Entity()
    {

    }

    ~Entity()
    {

    }

    
    virtual void attack(int damageDealt);
    virtual void update();
    virtual void getTexture();
};