#pragma once
#include "../entities/entity.hpp"

class Tower: public Entity
{
protected:
    int damage;
    int attackSpeed;
public:
    Tower()
    {

    }

    ~Tower()
    {

    }

    virtual void attack();

};