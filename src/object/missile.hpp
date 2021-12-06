#pragma once

#include "object.hpp"
#include "../enemies/enemy.hpp"
#include "../util/dataHolder.hpp"

class Missile: public Object
{
private:
    Enemy* target;
public:
    Missile(Enemy* e, Vec2D pos, int dam);

    bool update(DataHolder* holder);

};