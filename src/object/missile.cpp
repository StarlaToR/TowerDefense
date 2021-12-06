#include "missile.hpp"

Missile::Missile(Vec2D targetPos, Vec2D pos, float lRotation, int dam)
{
    target = targetPos;
    position = pos;
    rotation = lRotation;
    damage = dam;
    motion = Vec2D(cosf(lRotation)*8.0f,sinf(lRotation)*8.0f);
}

bool Missile::update(std::forward_list<Enemy*>* enemies)
{
    Vec2D dif = target - position;
    if(dif.getLength() <= 0.1f)
    {
        for (std::forward_list<Enemy *>::iterator i = enemies->begin(); i != enemies->end(); i++)
        {
            float dist = ((*i)->getPosition()-target).getLength();
            if(dist <= 1.5f)
            {
                (*i)->getDamage(damage*(dist/1.5f));
            }
        }
        return true;
    }
    else
    {
        position = position + motion / 60.0f;
    }
    return false;
}