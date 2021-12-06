#include "missile.hpp"

Missile::Missile(Enemy* e, Vec2D pos, int dam)
{
    target = e;
    position = pos;
    rotation = 0;
    damage = dam;
}

bool Missile::update(std::forward_list<Enemy*>* enemies)
{
    Vec2D dif = target->getPosition() - position;
    if(dif.getLength() <= 0.1f)
    {
        target->getDamage(damage);
        for (std::forward_list<Enemy *>::iterator i = enemies->begin(); i != enemies->end(); i++)
        {
            if(((*i)->getPosition()-target->getPosition()).getLength() <= 0.5f)
            {
                (*i)->getDamage(damage);
            }
        }
        return true;
    }
    else
    {
        float tmpDir;
        if (dif.x == 0)
        {
            if (dif.y > 0)
                tmpDir = PI / 2.0f;
            else
                tmpDir = -PI / 2.0f;
        }
        else
        {
            tmpDir = (atanf(dif.y / dif.x));
            if (dif.x < 0)
            {
                tmpDir += PI;
            }
        }
        rotation = tmpDir;
        position.x += 4.0f / 60.0f * cosf(rotation);
        position.y += 4.0f / 60.0f * sinf(rotation);
    }
    return false;
}