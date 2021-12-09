#include "particle.hpp"

class HealParticle : public Particle
{
protected:
    int counter = 0;
public:
    HealParticle() {position = Vec2D();}
    HealParticle(Vec2D pos);
    ~HealParticle() {}

    void drawParticle() override;
    bool shouldDelete() override;
    void updateParticle() override;
};