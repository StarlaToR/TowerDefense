#pragma once
#include "tower.hpp"

class SlowingTower : public Tower
{
private:
    int slowingTime;
public:
    SlowingTower(Vec2D pos, Sound* sound);

    SlowingTower():SlowingTower(Vec2D(0,0), nullptr){}

    void attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles) override;
    int getTexture();
    void upgrade();
    const char* getName() override {return "Slowing Tower";}
};