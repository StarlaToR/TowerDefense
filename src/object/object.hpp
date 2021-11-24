#pragma once
#include "../util/mathHelper.hpp"

class Object
{
protected:
    Vec2D position;
    float rotation;
    int damage;
public:
    Vec2D getPosition()
    {
        return this->position;
    }

    float getRotation()
    {
        return this->rotation;
    }
};