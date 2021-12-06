#pragma once

#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower(Vec2D pos);
    ClassicTower() : ClassicTower(Vec2D(0,0)) {}

    void attack(Enemy* e,std::forward_list<Missile*> missiles);
    int getTexture();
};