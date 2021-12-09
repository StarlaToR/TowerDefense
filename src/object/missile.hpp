#pragma once

#include "object.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>
#include <list>

class Missile: public Object
{
private:
    Vec2D target;
    Vec2D motion;
    unsigned int color;
public:
    Missile(Vec2D targetPos, Vec2D pos, float lRotation, int dam, unsigned int col);

    bool update(std::list<Enemy*>* enemies);

    unsigned int getColor() {return color;}

};