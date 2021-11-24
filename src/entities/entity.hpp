#pragma once
#include "../util/mathHelper.hpp"

class Entity
{
protected:
    Vec2D position;
    float rotation;
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

    Vec2D getPosition()
    {
        return this->position;
    }

    float getRotation()
    {
        return this->rotation;
    }
};