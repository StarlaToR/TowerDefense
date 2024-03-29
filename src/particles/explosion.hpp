#pragma once

#include "particle.hpp"

class ExplosionParticle : public Particle
{
protected:
    int counter = 0;
    int subColor;
public:
    ExplosionParticle();
    ExplosionParticle(Vec2D pos);
    ~ExplosionParticle() {}

    void drawParticle(Texture2D& asset, Tiles& tiles) override;
    bool shouldDelete() override;
    void updateParticle() override;
};