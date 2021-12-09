#include "gameUtil.hpp"

Tower* handleTowers(std::forward_list<Tower*>* towers, std::list<Enemy*>* enemies, std::forward_list<Missile*>* missiles, Tower* selectedTower, Vec2D camPos, float camScale)
{
    Vec2D mousePos = (Vec2D(GetMouseX(),GetMouseY())) / (48*camScale) - (Vec2D(50, 50)-camPos)/48.0f;
    for (std::forward_list<Tower*>::iterator i = towers->begin(); i != towers->end(); i++)
    {
        (*i)->update(enemies, missiles);

        if(mousePos.x >= (*i)->getPosition().x - 0.5 && mousePos.x <= (*i)->getPosition().x + 0.5 && mousePos.y >= (*i)->getPosition().y - 0.5 && mousePos.y <= (*i)->getPosition().y + 0.5)
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                return *i;
            }
        }
    }
    return selectedTower;
}

void handleMissiles(std::forward_list<Missile *> *missiles, std::list<Enemy *> *enemies, std::forward_list<Particle *> *particles)
{
    std::forward_list<Missile *>::iterator oldM = missiles->before_begin();
    for (std::forward_list<Missile *>::iterator i = missiles->begin(); i != missiles->end();)
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

void handleEnemies(TileMap *map, int *money, std::list<Enemy *> *enemies, std::forward_list<Particle *> *particles, int &playerLife)
{
    for (std::list<Enemy *>::iterator i = enemies->begin(); i != enemies->end();)
    {
        if ((*i)->update(map, enemies, particles, playerLife))
        {
            for (int j = 0; j < 15; j++) particles->push_front(new EnemyExplosionParticle((*i)->getPosition()));
            *money += (*i)->getReward();
            delete *i;
            i = enemies->erase(i);
        }
        else
        {
            i++;
        }
    }
}

void handleParticles(std::forward_list<Particle *> *particles)
{
    std::forward_list<Particle *>::iterator oldP = particles->before_begin();
    for (std::forward_list<Particle *>::iterator i = particles->begin(); i != particles->end();)
    {
        (*i)->updateParticle();
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

void placeTileAt(TileMap *map, Vec2D pos, Vec2D *drag, unsigned char tile, bool deco)
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
                    map->setTileAt((tile == START_EAST ? map->startPos : map->endPos), map->getDefaultTile(map->getTileAt((tile == START_EAST ? map->startPos : map->endPos))));
                    map->setTileAt((tile == START_EAST ? map->startPos : map->endPos), UNDEFINED, true);
                    map->setTileAt(pos, map->getTileAt(pos) + (tile == START_EAST ? 23 : 27), true);
                    map->setTileAt(pos, map->getTileAt(pos) + (tile == START_EAST ? 4 : 8));
                    (tile == START_EAST ? map->startPos : map->endPos) = pos;
                }
            }
            else if (!map->isRoad(old))
                map->setTileAt(pos, tile, true);
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
            map->setTileAt(pos, tile);
            map->setTileAt(pos, UNDEFINED, true);
        }
        *drag = pos;
    }
}

void handleEnemiesBuffer(TileMap *map, std::list<Enemy *> *enemies, std::forward_list<EnemySpawner> *buffer, int &waves)
{
    enemiesBuffer(map, enemies, buffer, waves);
    if (enemies->empty() && waves == 1)
    {
        
        for (int i = 0; i < 10; i++)
        {
            buffer->push_front((EnemySpawner){1, 50});
        }
        buffer->push_front((EnemySpawner){1, 0});

        waves++;
    }
    else if (enemies->empty() && waves == 2)
    {
        buffer->push_front((EnemySpawner){2, 60});
        buffer->push_front((EnemySpawner){3, 10});
        for (int i = 0; i < 20; i++)
        {
            buffer->push_front((EnemySpawner){1, 25});
        }
        waves++;
    }
}

void enemiesBuffer(TileMap *map, std::list<Enemy *> *enemies, std::forward_list<EnemySpawner> *buffer, int waves)
{
    for (std::forward_list<EnemySpawner>::iterator i = buffer->begin(); i != buffer->end();)
    {
        if ((i)->time > 0)
        {
            (i)->time -= 1;
            break;
        }

        switch ((i)->id)
        {
        case 1:
            enemies->push_back(new ClassicEnemy(map,waves));
            break;

        case 2:
            enemies->push_back(new BigEnemy(map,waves));
            break;

        case 3:
            enemies->push_back(new HealerEnemy(map,waves));
            break;

        default:
            break;
        }
        i = buffer->erase_after(buffer->before_begin());
    }
}
