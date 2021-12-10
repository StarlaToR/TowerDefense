#pragma once

#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"
#include "../object/missile.hpp"
#include "../particles/particle.hpp"
#include "../particles/explosion.hpp"
#include "../particles/enemy_explosion.hpp"
#include "../enemies/classicEnemy.hpp"
#include "../enemies/bigEnemy.hpp"
#include "../enemies/healerEnemy.hpp"
#include "../enemies/bossEnemy.hpp"
#include <forward_list>
#include <list>
#include "../tile/tileMap.hpp"

struct EnemySpawner
{
    int id;
    int time;
};

Tower* handleTowers(std::forward_list<Tower*>& towers, std::list<Enemy*>& enemies, std::forward_list<Missile*>& missiles, Tower* selectedTower, Vec2D camPos, float camScale);
void handleMissiles(std::forward_list<Missile*>& missiles, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles);
void handleEnemies(TileMap& map, int& money, std::list<Enemy*>& enemies, std::forward_list<Particle*>& particles, int &playerLife);
void handleParticles(std::forward_list<Particle*>& particles);
void placeTileAt(TileMap& map, Vec2D pos, Vec2D& drag, unsigned char tile, bool deco);
void handleEnemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int &waves);
void enemiesBuffer(TileMap& map, std::list<Enemy *>& enemies, std::forward_list<EnemySpawner>& buffer, int waves);
