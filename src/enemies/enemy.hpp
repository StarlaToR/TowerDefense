#pragma once
#include "../entities/entity.hpp"

class Enemy : public Entity
{
    protected:
        int speed;
        int reward;
    
    public:
    virtual void update() = 0;

};