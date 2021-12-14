#pragma once
#include "tower.hpp"
#include "../object/missile.hpp"

class ExplosiveTower : public Tower
{
private:
    int missilesUsed;
public:
    ExplosiveTower(Vec2D pos, Sound* );

    ExplosiveTower():ExplosiveTower(Vec2D(0,0), nullptr){}

    void upgrade();
    bool attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles) override;
    int getTexture();
    const char* getName() override {return "Rocket Launcher tower";}
};