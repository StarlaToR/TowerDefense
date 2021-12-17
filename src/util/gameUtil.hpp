#pragma once

#include <forward_list>
#include <list>
#include "../tile/tileMap.hpp"

struct EnemySpawner
{
    int id;
    int time;
};

class Tower;
class Enemy;
class Missile;
class Particle;

Tower* handleTowers(std::forward_list<Tower*>& towers, std::list<Enemy*>& enemies, std::forward_list<Missile*>& missiles, std::forward_list<Particle*>& particles, Tower* selectedTower, Vec2D camPos, float camScale);
void handleMissiles(std::forward_list<Missile*>& missiles, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles);
void handleEnemies(TileMap& map, int& money, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife);
void handleParticles(std::forward_list<Particle*>& particles);
void placeTileAt(TileMap& map, Vec2D pos, Vec2D& drag, unsigned char tile, bool deco);
void handleEnemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int &waves, int &difficulty);
void enemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int waves, int difficulty);
