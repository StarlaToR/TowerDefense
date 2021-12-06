#pragma once

#include <raylib.h>
#include <cstddef>
#include <forward_list>
#include "../tile/tileMap.hpp"
#include "../tile/tiles.hpp"
#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"
#include "../object/missile.hpp"
#include "../particles/particle.hpp"
#include "../particles/explosion.hpp"
#include "gameUtil.hpp"
#include "../tile/tileHolder.hpp"

typedef enum GameState
{
    INTRO,
    MENU,
    GAMEPLAY,
    LOAD,
    OPTION,
    CREDIT,
    EXIT,

} GameState;

class DataHolder
{
public:
    const int screenWidth  = 1600;
    const int screenHeight = 900;
    GameState gameState = INTRO;
    size_t framecounter = 0;
    Texture2D logo;
    Texture2D tileTexture;
    Texture2D background;
    Texture2D button;
    Texture2D credit;
    Texture2D title;
    Texture2D logoIsart;
    Font fontButton;
    Font fontTitle;
    TileMap map;
    Tiles tiles = Tiles();
    Vec2D mousePos;
    bool closeWindow = false;
    int buttonSelected;
    RenderType tileRenderType = EXTENDED;
    Vec2D dragPos = Vec2D(-1,-1);
    std::forward_list<Enemy*> enemies = std::forward_list<Enemy*>();
    std::forward_list<Tower*> towers = std::forward_list<Tower*>();
    std::forward_list<Missile*> missiles = std::forward_list<Missile*>();
    std::forward_list<Particle*> particles = std::forward_list<Particle*>();
    TileHolders holders = TileHolders();

    int money = 0;

    DataHolder() {}
    ~DataHolder() {}
    void unloadDatas();
    void handleGameState();
};