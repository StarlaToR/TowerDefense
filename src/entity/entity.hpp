#pragma once
#include "../util/mathHelper.hpp"

class Entity
{
protected:
    Vec2D position;
    float rotation;
    int health;
    int maxHealth;

public:
    Entity()
    {

    }

    ~Entity()
    {

    }

    virtual int getAttacked(int damage)
    {
        health -= damage;
        if(health <= 0)
        {
            
        }
        
    }

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