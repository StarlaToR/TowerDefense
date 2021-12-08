#pragma once

#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"
#include "../object/missile.hpp"
#include "../particles/particle.hpp"
#include "../particles/explosion.hpp"
#include "../enemies/classicEnemy.hpp"
#include "../enemies/bigEnemy.hpp"
#include "../enemies/healerEnemy.hpp"
#include <forward_list>
#include "../tile/tileMap.hpp"

struct EnemySpawner
{
    int id;
    int time;
};

Tower* handleTowers(std::forward_list<Tower*>* towers, std::forward_list<Enemy*>* enemies, std::forward_list<Missile*>* missiles, Tower* selectedTower);
void handleMissiles(std::forward_list<Missile*>* missiles, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles);
void handleEnemies(TileMap* map, int* money, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles);
void handleParticles(std::forward_list<Particle*>* particles);
void placeTileAt(TileMap* map, Vec2D pos, Vec2D* drag, unsigned char tile, bool deco);
void handleEnemiesBuffer(TileMap *map, std::forward_list<Enemy *> *enemies, std::forward_list<EnemySpawner> *buffer, int &waves);
void enemiesBuffer(TileMap *map, std::forward_list<Enemy *> *enemies, std::forward_list<EnemySpawner> *buffer);
