#pragma once

#include "tower.hpp"

class ClassicTower : public Tower
{
public:
    ClassicTower(Vec2D pos);
    ClassicTower() : ClassicTower(Vec2D(0,0)) {}

    void attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles) override;
    void upgrade();
    int getTexture();
    const char* getName() override {return "Gun Tower";}
};