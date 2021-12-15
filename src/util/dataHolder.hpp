#pragma once

#include <raylib.h>
#include <cstddef>
#include <forward_list>
#include <list>
#include "../tile/tileMap.hpp"
#include "../tile/tiles.hpp"
#include "../enemies/enemy.hpp"
#include "../towers/tower.hpp"
#include "../object/missile.hpp"
#include "../particles/particle.hpp"
#include "../particles/explosion.hpp"
#include "gameUtil.hpp"
#include "../tile/tileHolder.hpp"
#include "../towers/towerHolder.hpp"
#include "timeCounter.hpp"

typedef enum GameState : int
{
    INTRO,
    MENU,
    MENUPLAY,
    MENUMAP,
    MENUMAPCUSTOM,
    GAMEPLAY,
    GAMEOVER,
    VICTORY,
    EDITOR,
    LOAD,
    OPTION,
    GAMEOPTION,
    CREDIT,
    EXIT,

} GameState;

struct TextureHolder
{
    Texture2D logo;
    Texture2D boss;
    Texture2D tileTexture;
    Texture2D background;
    Texture2D button;
    Texture2D credit;
    Texture2D title;
    Texture2D logoIsart;
    Texture2D gameUI;
    Texture2D board;
    Texture2D optionButton;
};

struct SoundHolder
{
    Sound buttonSound;
    Music musicTroll;
    Music gameplayMusic;
    Music introSong;
    Sound classicTowerSound;
    Sound slowTowerSound;
    Sound explosiveTowerSound;
};

struct ListHolder
{
    TileMap map;
    Tiles tiles = Tiles();
    std::list<Enemy*> enemies = std::list<Enemy*>();
    std::forward_list<Tower*> towers = std::forward_list<Tower*>();
    std::forward_list<Missile*> missiles = std::forward_list<Missile*>();
    std::forward_list<Particle*> particles = std::forward_list<Particle*>();
    std::forward_list<EnemySpawner> buffer = std::forward_list<EnemySpawner>();
    TileHolders tHolders = TileHolders();
    TowerHolders towerHolders = TowerHolders();
};

class InputHelper
{
    private:
    bool left = false;
    bool right = false;
    public:
    bool isLeftPressed();
    bool isRightPressed();
    void handleInputs();
};

class DataHolder
{
public:
    const int screenWidth  = 1600;
    const int screenHeight = 900;
    GameState gameState = INTRO;
    size_t framecounter = 0;
    TextureHolder textures;
    SoundHolder sounds;
    ListHolder lists;
    InputHelper inputs;
    Font fontButton;
    Font fontTitle;
    Vec2D mousePos;
    bool closeWindow = false;
    int buttonSelected = 0;
    int holderHovered = 0;
    int holderSelected = 0;
    TimeCounter timeCounter;
    float masterVolume = 0.6f;
    float effectVolume = 0.5f;
    int saveSlot = 0;
    char maxLevel = 0;
    RenderType tileRenderType = EXTENDED;
    Vec2D dragPos = Vec2D(-1,-1);
    Vec2D cameraPos = Vec2D();
    char cameraScale = 1;
    int wave;
    Tower* selectedTower =nullptr;
    int gameSpeed = 1;
    bool onPause = false;
    int money = 20;
    int life;

    DataHolder() {}
    ~DataHolder() {}
    void unloadDatas();
    void initDatas();
    void handleGameState();
};