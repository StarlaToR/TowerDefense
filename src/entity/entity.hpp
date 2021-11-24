#pragma once
#include "../util/mathHelper.hpp"

class Entity
{
protected:
    Vec2D position;
    float rotation;

public:
    Entity()
    {

    }

    ~Entity()
    {

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