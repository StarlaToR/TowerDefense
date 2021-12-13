#pragma once

#include "particle.hpp"

class Laser : public Particle
{
protected:
    int counter = 0;
    unsigned int color = 0x00ff00ff;
    Vec2D targetPos = Vec2D();
public:
    Laser() {position = Vec2D();}
    Laser(Vec2D pos, Vec2D target, unsigned int col);
    ~Laser() {}

    void drawParticle(Texture2D& asset, Tiles& tiles) override;
    bool shouldDelete() override;
    void updateParticle() override;
};