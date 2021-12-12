#include "particle.hpp"

class HealParticle : public Particle
{
protected:
    int counter = 0;
    bool alt = false;
public:
    HealParticle() {position = Vec2D();}
    HealParticle(Vec2D pos);
    ~HealParticle() {}

    void drawParticle(Texture2D& asset, Tiles& tiles) override;
    bool shouldDelete() override;
    void updateParticle() override;
};