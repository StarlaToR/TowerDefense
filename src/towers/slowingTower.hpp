#pragma once
#include "tower.hpp"

class SlowingTower : public Tower
{
private:
    int slowingTime;
public:
    SlowingTower(Vec2D pos);

    SlowingTower():SlowingTower(Vec2D(0,0)){}

    void attack(Enemy* e,std::forward_list<Missile*>& missiles);
    int getTexture();
    void upgrade();
    const char* getName() override {return "Slowing Tower";}
};