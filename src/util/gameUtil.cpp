#include "gameUtil.hpp"

Tower* handleTowers(std::forward_list<Tower*>& towers, std::list<Enemy*>& enemies, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles, Tower* selectedTower, Vec2D camPos, float camScale)
{
    Vec2D mousePos = (Vec2D(GetMouseX(),GetMouseY())) / (48*camScale) - (Vec2D(50, 50)-camPos)/48.0f;
    Vec2D mousePosR = (Vec2D(GetMouseX(),GetMouseY()));
    bool insideMap = (mousePosR.x > 50 && mousePosR.y > 50 && mousePosR.x < 1202 && mousePosR.y < 626);
    for (std::forward_list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++)
    {
        (*i)->update(enemies, missiles, particles);

        if(insideMap && mousePos.x >= (*i)->getPosition().x - 0.5 && mousePos.x <= (*i)->getPosition().x + 0.5 && mousePos.y >= (*i)->getPosition().y - 0.5 && mousePos.y <= (*i)->getPosition().y + 0.5)
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                return *i;
            }
        }
    }
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && insideMap) ? nullptr : selectedTower;
}

void handleMissiles(std::forward_list<Missile *>& missiles, std::list<Enemy *>& enemies, std::forward_list<Particle *>& particles)
{
    std::forward_list<Missile *>::iterator oldM = missiles.before_begin();
    for (std::forward_list<Missile *>::iterator i = missiles.begin(); i != missiles.end();)
    {
        if ((*i)->update(enemies))
        {
            particles.push_front(new BigExplosionParticle((*i)->getPosition()));
            for (int it = 0; it < 7; it++) particles.push_front(new ExplosionParticle((*i)->getPosition()));
            delete *i;
            i = missiles.erase_after(oldM);
        }
        else
        {
            oldM = i;
            i++;
        }
    }
}

void handleEnemies(TileMap& map, int& money, std::list<Enemy *>& enemies, std::forward_list<Particle *>& particles, int& playerLife)
{
    std::list<Enemy *>::iterator it = enemies.begin();
    while (it != enemies.end())
    {
        if ((*it)->update(map, enemies, particles, playerLife))
        {
            particles.push_front(new EnemyExplosionParticle((*it)->getPosition()));
            money += (*it)->getReward();
            delete *it;
            it = enemies.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void handleParticles(std::forward_list<Particle *>& particles)
{
    std::forward_list<Particle *>::iterator oldP = particles.before_begin();
    for (std::forward_list<Particle *>::iterator i = particles.begin(); i != particles.end();)
    {
        (*i)->updateParticle();
        if ((*i)->shouldDelete())
        {
            delete *i;
            i = particles.erase_after(oldP);
        }
        else
        {
            oldP = i;
            i++;
        }
    }
}

void placeTileAt(TileMap& map, Vec2D pos, Vec2D& drag, unsigned char tile, bool deco)
{
    if (pos.x >= 0 && pos.y >= 0 && pos.x < map.getWidth() && pos.y < map.getHeight())
    {
        if (deco)
        {
            unsigned char old = map.getTileAt(pos);
            if (tile == START_EAST || tile == END_EAST)
            {
                if (map.isValidStartEnd(old))
                {
                    map.setTileAt((tile == START_EAST ? map.startPos : map.endPos), map.getDefaultTile(map.getTileAt((tile == START_EAST ? map.startPos : map.endPos))));
                    map.setTileAt((tile == START_EAST ? map.startPos : map.endPos), UNDEFINED, true);
                    map.setTileAt(pos, map.getTileAt(pos) + (tile == START_EAST ? 23 : 27), true);
                    map.setTileAt(pos, map.getTileAt(pos) + (tile == START_EAST ? 4 : 8));
                    (tile == START_EAST ? map.startPos : map.endPos) = pos;
                }
            }
            else if (!map.isRoad(old))
                map.setTileAt(pos, tile, true);
        }
        else if (tile == ROAD_STRAIGHT_EASTWEST)
        {
            if (drag.x > -0.9f && (pos - drag).lengthSquared() < 1.1 && (pos - drag).lengthSquared() > 0.9)
            {
                map.drawRoad(drag, Direction(pos - drag));
            }  
        }
        else
        {
            map.setTileAt(pos, tile);
            map.setTileAt(pos, UNDEFINED, true);
        }
        drag = pos;
    }
}

void handleEnemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int &waves)
{
    enemiesBuffer(map, enemies, buffer, waves);
    if (enemies.empty() && buffer.empty())
    {
        if (waves%5 == 4 && waves > 0)
        {
            for (int i = 0; i < waves/5+1; i++)
            {
                buffer.push_front((EnemySpawner){3, 7});
            }
        }
        for (int i = 0; i < (waves%2==0?waves:2*waves); i++)
            {
                buffer.push_front((EnemySpawner){2, 50-(waves<20?2*waves:40)});
            }
        for (int i = 0; i < 10+waves; i++)
        {
            buffer.push_front((EnemySpawner){1, 50-(waves<20?2*waves:40)});
        }
        buffer.push_front((EnemySpawner){1, waves==0?300:0});
        if (waves == 24)
        {
            buffer.push_front((EnemySpawner){4, 120});
        }

        waves++;
    }
}

void enemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int waves)
{
    for (std::forward_list<EnemySpawner>::iterator i = buffer.begin(); i != buffer.end();)
    {
        if ((i)->time > 0)
        {
            (i)->time -= 1;
            break;
        }

        switch ((i)->id)
        {
        case 1:
            enemies.push_back(new ClassicEnemy(map,waves));
            break;

        case 2:
            enemies.push_back(new BigEnemy(map,waves));
            break;

        case 3:
            enemies.push_back(new HealerEnemy(map,waves));
            break;
        case 4:
            enemies.push_back(new BossEnemy(map,waves));
            break;

        default:
            break;
        }
        i = buffer.erase_after(buffer.before_begin());
    }
}
