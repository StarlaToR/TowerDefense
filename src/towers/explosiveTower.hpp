#pragma once
#include "tower.hpp"

class ExplosiveTower : public Tower
{
public:
    ExplosiveTower(Vec2D pos);

    ExplosiveTower():ExplosiveTower(Vec2D(0,0)){}

    
    void attack(Enemy* e);
    int getTexture();
};