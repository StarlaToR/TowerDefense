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

    virtual int getAttacked(int damage);
    virtual void attack();
    virtual void update();
    virtual void getTexture();
};