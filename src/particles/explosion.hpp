#include "particle.hpp"

class ExplosionParticle : public Particle
{
protected:
    int counter = 0;
public:
    ExplosionParticle() {position = Vec2D();}
    ExplosionParticle(Vec2D pos) {position = pos;}
    ~ExplosionParticle() {}

    void drawParticle() override;
    bool shouldDelete() override;
};