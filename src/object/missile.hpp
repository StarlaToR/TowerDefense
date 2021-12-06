#pragma once

#include "object.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>

class Missile: public Object
{
private:
    Vec2D target;
    Vec2D motion;
public:
    Missile(Vec2D targetPos, Vec2D pos, float lRotation, int dam);

    bool update(std::forward_list<Enemy*>* enemies);

};