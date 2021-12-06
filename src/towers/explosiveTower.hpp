#pragma once
#include "tower.hpp"
#include "missile.hpp"

class ExplosiveTower : public Tower
{
public:
    ExplosiveTower(Vec2D pos);

    ExplosiveTower():ExplosiveTower(Vec2D(0,0)){}

    
    void attack(Enemy* e, std::forward_list<Missile*> missiles);
    int getTexture();
};