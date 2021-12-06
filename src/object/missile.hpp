#pragma once

#include "object.hpp"
#include "../enemies/enemy.hpp"
#include <forward_list>

class Missile: public Object
{
private:
    Enemy* target;
public:
    Missile(Enemy* e, Vec2D pos, int dam);

    bool update(std::forward_list<Enemy*> enemies);

};