#pragma once
#include "../entities/entity.hpp"

class Tower: public Entity
{
protected:
    int range;
    int cost;
public:
    Tower()
    {

    }

    ~Tower()
    {

    }
};