#include "missile.hpp"

Missile::Missile(Enemy* e, Vec2D pos, float rot, int dam)
{
    target = e;
    position = pos;
    rotation = rot;
    damage = dam;
}

bool Missile::update(DataHolder* holder)
{
    Vec2D dif = target->getPosition() - position;
    if(dif.getLength() <= 0.1f)
    {
        target->getDamage(damage);
        for (std::forward_list<Enemy *>::iterator i = holder->enemies.begin(); i != holder->enemies.end(); i++)
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