#include "towerHolder.hpp"

TowerHolder::TowerHolder(Vec2D pos, int type)
{
    position = pos;
    towerType = type;
    isUsed = false;
}

TowerHolder::TowerHolder()
{
}

TowerHolder::~TowerHolder()
{

}

void TowerHolder::update(std::forward_list<Tower*>* towers, TileMap* map)
{
    if(IsMouseButtonPressed(1))
    {
        if (GetMouseX() >= position.x && GetMouseX() <= position.x + 128 && GetMouseY() >= position.y && GetMouseY() <= position.y + 128)
        {
            isUsed = true;
        }
    }
    if(IsMouseButtonReleased(1) && isUsed)
    {
        Vec2D pos((int)((GetMouseX() - 50) /48), (int)((GetMouseY() - 50) /48));
        if(pos.x >= 0 && pos.x <= MAP_WIDTH && pos.y >= 0 && pos.y <= MAP_HEIGHT)
        {
            if (map->isTileWithTower(pos))
            {
                map->setTileWithTower(pos);

                if(towerType == 0)
                    towers->push_front(new ClassicTower(pos));
                if(towerType == 1)
                    towers->push_front(new SlowingTower(pos));
                if(towerType == 2)
                    towers->push_front(new ExplosiveTower(pos));
            }
        }
        isUsed = false;
    }
}