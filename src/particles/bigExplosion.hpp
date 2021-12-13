#pragma once

#include "particle.hpp"

class BigExplosionParticle : public Particle
{
protected:
    int counter = 0;
public:
    BigExplosionParticle() {position = Vec2D();}
    BigExplosionParticle(Vec2D pos);
    ~BigExplosionParticle() {}

    void drawParticle(Texture2D& asset, Tiles& tiles) override;
    bool shouldDelete() override;
    void updateParticle() override;
};