#pragma once

#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"
#include "../object/missile.hpp"
#include "../particles/particle.hpp"
#include "../particles/explosion.hpp"
#include <forward_list>
#include "../tile/tileMap.hpp"

void handleTowers(std::forward_list<Tower*>* towers, std::forward_list<Enemy*>* enemies, std::forward_list<Missile*>* missiles);
void handleMissiles(std::forward_list<Missile*>* missiles, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles);
void handleEnemies(TileMap* map, int* money, std::forward_list<Enemy*>* enemies, std::forward_list<Particle*>* particles);
void handleParticles(std::forward_list<Particle*>* particles);