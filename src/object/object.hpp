#pragma once
#include "../util/mathHelper.hpp"

class Object
{
protected:
    Vec2D position;
    float rotation;
    int damage;
public:
    Object()
    {

    }

    ~Object()
    {

    }

    Vec2D getPosition()
    {
        return this->position;
    }

    float getRotation()
    {
        return this->rotation;
    }
};