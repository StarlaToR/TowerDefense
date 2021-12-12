#pragma once

#include "particle.hpp"

class EnemyExplosionParticle : public Particle
{
protected:
    int counter = 0;
    int subColor;
public:
    EnemyExplosionParticle() : subColor(0) {position = Vec2D();}
    EnemyExplosionParticle(Vec2D pos);
    ~EnemyExplosionParticle() {}

    void drawParticle(Texture2D& asset, Tiles& tiles) override;
    bool shouldDelete() override;
    void updateParticle() override;
};