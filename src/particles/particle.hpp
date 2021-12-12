#pragma once
#include "../object/object.hpp"
#include "../tile/tiles.hpp"

class Particle : public Object
{
protected:
    Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize);

public:
    Particle()
    {
        
    }
    virtual ~Particle() = 0;
    virtual void drawParticle(Texture2D& asset, Tiles& tiles) = 0;
    virtual void updateParticle() = 0;
    virtual bool shouldDelete() = 0;
};