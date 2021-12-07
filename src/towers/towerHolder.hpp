#include "tower.hpp"
#include "classicTower.hpp"
#include "slowingTower.hpp"
#include "explosiveTower.hpp"
#include <forward_list>

class TowerHolder
{
private:
    int towerType;
    Vec2D position;
    bool isUsed;

public:
    TowerHolder(Vec2D pos,int type);
    TowerHolder();
    ~TowerHolder();
    
    int getTexture();
    void update(std::forward_list<Tower*>* towers, TileMap* map);
};