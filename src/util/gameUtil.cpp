#include "gameUtil.hpp"

void handleTowers(std::forward_list<Tower*>* towers, std::forward_list<Enemy*>* enemies, std::forward_list<Missile*>* missiles)
{
    for (std::forward_list<Tower*>::iterator i = towers->begin(); i != towers->end(); i++)
    {
        (*i)->update(enemies, missiles);
    }
}

void handleMissiles(std::forward_list<Missile*>* missiles, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles)
{
    std::forward_list<Missile*>::iterator oldM = missiles->before_begin();
    for (std::forward_list<Missile*>::iterator i = missiles->begin(); i != missiles->end();)
    {
        if ((*i)->update(enemies))
        {
            particles->push_front(new ExplosionParticle((*i)->getPosition()));
            delete *i;
            i = missiles->erase_after(oldM);
        }
        else
        {
            oldM = i;
            i++;
        }
    }
}

void handleEnemies(TileMap* map, int* money, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles)
{
    std::forward_list<Enemy*>::iterator oldE = enemies->before_begin();
    for (std::forward_list<Enemy*>::iterator i = enemies->begin(); i != enemies->end();)
    {
        if ((*i)->update(map, enemies, particles))
        {
            *money += (*i)->getReward();
            delete *i;
            i = enemies->erase_after(oldE);
        }
        else
        {
            oldE = i;
            i++;
        }
    }
}

void handleParticles(std::forward_list<Particle*>* particles)
{
    std::forward_list<Particle*>::iterator oldP = particles->before_begin();
    for (std::forward_list<Particle*>::iterator i = particles->begin(); i != particles->end();)
    {
        if ((*i)->shouldDelete())
        {
            delete *i;
            i = particles->erase_after(oldP);
        }
        else
        {
            oldP = i;
            i++;
        }
    }
}