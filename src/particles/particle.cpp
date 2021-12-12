#include "particle.hpp"

Particle::~Particle()
{
}

Rectangle Particle::toRayLibRectangle(Vec2D origin, Vec2D rectSize)
{
    return (Rectangle){origin.x, origin.y, rectSize.x, rectSize.y};
}