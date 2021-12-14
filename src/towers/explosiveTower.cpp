#include "explosiveTower.hpp"

ExplosiveTower::ExplosiveTower(Vec2D pos)
{
    damage = 25;
    range = 4;
    health = 150;
    maxHealth = 150;
    attackSpeed = 75;
    attackCooldown = 0;
    cost = 50;
    position = pos + Vec2D(0.5f,0.5f);
    rotation = 0;
    angularVelocity = 0.07f;
    missilesUsed = 0;
    level = 1;
    textureID = 99;
}

void ExplosiveTower::attack(Enemy* e, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles)
{
    
    attackCooldown = attackSpeed;
    missilesUsed ++;
    if (level < 4)
    {
        if (missilesUsed > 4)
            missilesUsed = 0;
        else
            missiles.push_front(new Missile(e->getPosition(), getPosition()+Vec2D(cosf(rotation)*0.5f,sinf(rotation)*0.5f), rotation, damage, getColor()));
    }
    else
    {
        if (missilesUsed > 6)
            missilesUsed = 0;
        else
            missiles.push_front(new Missile(e->getPosition(), getPosition()+Vec2D(cosf(rotation)*0.5f,sinf(rotation)*0.5f), rotation, damage, getColor()));
    }
}

int ExplosiveTower::getTexture()
{
    return textureID + missilesUsed;
}

void ExplosiveTower::upgrade()
{
    if(level < 4)
    {
        level += 1;
        damage += 15;
        textureID += 5;
        attackSpeed -= 10;
        missilesUsed = 0;
    }
}