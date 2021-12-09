#pragma once
#include "../object/object.hpp"

class Particle : public Object
{
protected:
    

public:
    Particle()
    {
        
    }
    virtual ~Particle() = 0;
    virtual void drawParticle() = 0;
    virtual void updateParticle() = 0;
    virtual bool shouldDelete() = 0;
};