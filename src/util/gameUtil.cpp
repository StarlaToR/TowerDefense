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

void placeTileAt(TileMap* map, Vec2D pos, Vec2D* drag, unsigned char tile, bool deco)
{
    if (pos.x >= 0 && pos.y >= 0 && pos.x < map->getWidth() && pos.y < map->getHeight())
    {
        if (deco)
        {
            unsigned char old = map->getTileAt(pos);
            if (tile == START_EAST || tile == END_EAST)
            {
                if (map->isValidStartEnd(old))
                {
                    map->setTileAt((tile == START_EAST ? map->startPos : map->endPos),map->getDefaultTile(map->getTileAt((tile == START_EAST ? map->startPos : map->endPos))));
                    map->setTileAt((tile == START_EAST ? map->startPos : map->endPos),UNDEFINED,true);
                    map->setTileAt(pos,map->getTileAt(pos)+(tile == START_EAST ? 23 : 27),true);
                    map->setTileAt(pos,map->getTileAt(pos)+(tile == START_EAST ? 4 : 8));
                    (tile == START_EAST ? map->startPos : map->endPos) = pos;
                }
            }
            else if (!map->isRoad(old)) map->setTileAt(pos,tile,true);
        }
        else if (tile == ROAD_STRAIGHT_EASTWEST)
        {
            if (drag->x > -0.9f && (pos - *drag).lengthSquared() < 1.1 && (pos - *drag).lengthSquared() > 0.9)
            {
                map->drawRoad(*drag, Direction(pos - *drag));
            }
        }
        else
        {
            map->setTileAt(pos,tile);
            map->setTileAt(pos,UNDEFINED,true);
        }
        *drag = pos;
    }
}

void handleEnemiesBuffer(TileMap* map, std::forward_list<Enemy*>* enemies)
{
    for (int i = 0; i < 80; i++)
    {
        enemies->push_front(new ClassicEnemy(map));
        enemies->push_front(new BigEnemy(map));

        enemies->push_front(new HealerEnemy(map));

    }
}