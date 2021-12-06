#pragma once

#include <raylib.h>
#include <cstddef>
#include <forward_list>
#include "../tile/tileMap.hpp"
#include "../tile/tiles.hpp"
#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"

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

    DataHolder() {}
    ~DataHolder() {}
    void unloadDatas();
    void handleGameState();
};