#include <string>
#include "../towers/classicTower.hpp"
#include "dataHolder.hpp"

static void handleIntro(DataHolder &in);
static void handleMenu(DataHolder &in);
static void handleMenuPlay(DataHolder &in);
static void handleMenuMap(DataHolder &in);
static void handleMenuMapCustom(DataHolder &in);
static void handleGamePlay(DataHolder &in);
static void handleGamePause(DataHolder &in);
static void handleGameOver(DataHolder &in);
static void handleVictory(DataHolder &in);
static void handleEditor(DataHolder &in);
static void handleLoad(DataHolder &in);
static void handleOption(DataHolder &in);
static void handleGameOption(DataHolder &in);
static void handleSave(DataHolder &in);
static void handleCredit(DataHolder &in);

void (*handlers[15])(DataHolder &in) =
    {
        &handleIntro,
        &handleMenu,
        &handleMenuPlay,
        &handleMenuMap,
        &handleMenuMapCustom,
        &handleGamePlay,
        &handleGamePause,
        &handleGameOver,
        &handleVictory,
        &handleEditor,
        &handleLoad,
        &handleOption,
        &handleGameOption,
        &handleSave,
        &handleCredit,
};

void InputHelper::handleInputs()
{
    right = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    left = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

bool InputHelper::isLeftPressed()
{
    if (left)
    {
        left = false;
        return true;
    }
    return false;
}

bool InputHelper::isRightPressed()
{
    if (right)
    {
        right = false;
        return true;
    }
    return false;
}

void DataHolder::unloadDatas()
{
    for (std::list<Enemy *>::iterator i = lists.enemies.begin(); i != lists.enemies.end(); i++)
        delete *i;
    for (std::forward_list<Tower *>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++)
        delete *i;
    for (std::forward_list<Missile *>::iterator i = lists.missiles.begin(); i != lists.missiles.end(); i++)
        delete *i;
    for (std::forward_list<Particle *>::iterator i = lists.particles.begin(); i != lists.particles.end(); i++)
        delete *i;
    UnloadTexture(textures.logo);
    UnloadTexture(textures.tileTexture);
    UnloadTexture(textures.background);
    UnloadTexture(textures.title);
    UnloadTexture(textures.button);
    UnloadTexture(textures.buttonDown);
    UnloadTexture(textures.boss);
    UnloadTexture(textures.logoIsart);
    UnloadTexture(textures.gameUI);
    UnloadFont(fontButton);
    UnloadFont(fontTitle);
    UnloadSound(sounds.buttonSound);
    UnloadSound(sounds.classicTowerSound);
    UnloadSound(sounds.slowTowerSound);
    UnloadSound(sounds.explosiveTowerSound);
    UnloadMusicStream(sounds.musicTroll);
    UnloadMusicStream(sounds.introSong);
    UnloadMusicStream(sounds.gameplayMusic);
}

void DataHolder::initDatas()
{
    textures.logo = LoadTexture("assets/textures/logo.png");
    textures.logoIsart = LoadTexture("assets/textures/logo_isart.png");
    textures.boss = LoadTexture("assets/textures/boss.png");
    textures.background = LoadTexture("assets/textures/background.png");
    textures.title = LoadTexture("assets/textures/title.png");
    textures.tileTexture = LoadTexture("assets/textures/tileSheet.png");
    textures.button = LoadTexture("assets/textures/button.png");
    textures.buttonDown = LoadTexture("assets/textures/button_down.png");
    textures.gameUI = LoadTexture("assets/textures/ui.png");
    textures.board = LoadTexture("assets/textures/board.png");
    textures.optionButton = LoadTexture("assets/textures/optionButton.png");
    textures.buttonPause = LoadTexture("assets/textures/pause.png");
    textures.buttonSlowSpeed = LoadTexture("assets/textures/slowspeed.png");
    textures.buttonAccelerateSpeed = LoadTexture("assets/textures/acceleratespeed.png");
    textures.speedCounter = LoadTexture("assets/textures/speedcounter.png");
    sounds.buttonSound = LoadSound("assets/sounds/button.ogg");
    sounds.musicTroll = LoadMusicStream("assets/sounds/ouioui.ogg");
    sounds.gameplayMusic = LoadMusicStream("assets/sounds/gameplayMusic.ogg");
    sounds.introSong = LoadMusicStream("assets/sounds/introSong.ogg");
    sounds.classicTowerSound = LoadSound("assets/sounds/classicTower.ogg");
    sounds.slowTowerSound = LoadSound("assets/sounds/slowTower.ogg");
    sounds.explosiveTowerSound = LoadSound("assets/sounds/explosiveTower.ogg");
    fontButton = LoadFontEx("assets/font/ethnocentric.ttf", 100, 0, 0);
    fontTitle = LoadFontEx("assets/font/title.ttf", 100, 0, 0);
    lists.map = TileMap();
    SetMusicVolume(sounds.musicTroll, 0.15f);
    SetSoundVolume(sounds.classicTowerSound, 0.20f);
    SetSoundVolume(sounds.slowTowerSound, 0.10f);
    SetSoundVolume(sounds.explosiveTowerSound, 0.10f);
    SetSoundVolume(sounds.buttonSound, 0.50f);
    selectedTower = nullptr;
    lists.tiles.registerTiles();
    SetMasterVolume(masterVolume);
    lists.towerHolders.initTowers(&sounds.classicTowerSound, &sounds.slowTowerSound, &sounds.explosiveTowerSound);
    timeCounter = TimeCounter();
}

void DataHolder::handleGameState()
{
    inputs.handleInputs();
    UpdateMusicStream(sounds.musicTroll);
    UpdateMusicStream(sounds.gameplayMusic);
    UpdateMusicStream(sounds.introSong);
    if (GetMusicTimePlayed(sounds.musicTroll) >= GetMusicTimeLength(sounds.musicTroll) - 0.05f)
        StopMusicStream(sounds.musicTroll);
    if (GetMusicTimePlayed(sounds.introSong) >= GetMusicTimeLength(sounds.introSong) - 0.05f)
        StopMusicStream(sounds.introSong);
    mousePos = Vec2D(GetMousePosition().x, GetMousePosition().y);

    if (gameState < EXIT)
    {
        handlers[gameState](*this);
    }
    framecounter++;
}

void handleIntro(DataHolder &in)
{
    if (in.inputs.isLeftPressed() || in.framecounter > 360)
    {
        StopMusicStream(in.sounds.introSong);
        in.gameState = MENU;
    }
}

void handleMenu(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUPLAY;
        }
        else if (in.buttonSelected == 2)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = OPTION;
        }
        else if (in.buttonSelected == 3)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = CREDIT;
        }
        else if (in.buttonSelected == 4)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = EXIT;
        }
        else if (in.buttonSelected == 5)
        {
            PlaySound(in.sounds.buttonSound);
            if (IsMusicStreamPlaying(in.sounds.musicTroll))
            {
                StopMusicStream(in.sounds.musicTroll);
            }
            else
            {
                PlayMusicStream(in.sounds.musicTroll);
            }
        }
        else if (in.buttonSelected == 6)
        {
            in.framecounter = 0;
            PlaySound(in.sounds.buttonSound);
            PlayMusicStream(in.sounds.introSong);
            in.gameState = INTRO;
        }
    }
}

void handleMenuPlay(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.life = 20;
            in.wave = 0;
            in.money = 20;
            in.lists.saveDatas.maxLevel = 0;
            in.lists.saveDatas.timePlayed = 0;
            in.tileRenderType = NORMAL;
            in.gameState = MENUMAP;
        }
        if (in.buttonSelected == 2)
        {
            PlaySound(in.sounds.buttonSound);
            for (int i = 0; i < 3; i++)
            {
                loadFile(in.lists.renderDatas[i], i);
            }
            in.gameState = LOAD;
        }
        else if (in.buttonSelected == 3)
        {
            PlaySound(in.sounds.buttonSound);
            in.lists.map.loadFromFile("saves/maps/game/default.bin");
            in.tileRenderType = EXTENDED;
            in.gameState = EDITOR;
        }
        else if (in.buttonSelected == 4)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENU;
        }
    }
}

void handleMenuMap(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected >= 1 && in.buttonSelected <= 10)
        {
            std::string path = {"saves/maps/game/game0.bin"};
            path[20] = in.buttonSelected - 1 + '0';
            in.currentLevel = in.buttonSelected - 1;
            in.lists.map.loadFromFile(path.data());
            in.timeCounter.start();
            PlaySound(in.sounds.buttonSound);
            in.gameState = GAMEPLAY;
        }
        else if (in.buttonSelected == 11)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUPLAY;
        }
        else if (in.buttonSelected == 12)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUMAPCUSTOM;
        }
    }
}

void handleMenuMapCustom(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 11)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUMAP;
        }
        else
        {
            std::string path = {"saves/maps/custom/map0.bin"};
            path[21] = in.buttonSelected - 1 + '0';
            if (in.lists.map.loadFromFile(path.data()) >= 0)
            {
                in.currentLevel = -1;
                in.timeCounter.start();
                PlaySound(in.sounds.buttonSound);
                in.gameState = GAMEPLAY;
            }
        }
    }
}

void handleGamePlay(DataHolder &in)
{
    PlayMusicStream(in.sounds.gameplayMusic);
    int counter = 0;
    while (counter < in.gameSpeed)
    {
        handleEnemiesBuffer(in.lists.map, in.lists.enemies, in.lists.buffer, in.wave, in.difficulty);
        in.selectedTower = handleTowers(in.lists.towers, in.lists.enemies, in.lists.missiles, in.lists.particles, in.selectedTower, in.cameraPos, in.cameraScale);
        handleMissiles(in.lists.missiles, in.lists.enemies, in.lists.particles);
        handleEnemies(in.lists.map, in.money, in.lists.enemies, in.lists.particles, in.life);
        handleParticles(in.lists.particles);
        counter++;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        in.cameraPos = in.cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y) / in.cameraScale;
    }
    if (GetMouseWheelMove() > 0.1 && in.cameraScale < 3)
    {
        in.cameraScale++;
        in.cameraPos = in.cameraPos + Vec2D(300, 160) / (in.cameraScale == 2 ? 1 : 3);
    }
    if (GetMouseWheelMove() < -0.1 && in.cameraScale > 1)
    {
        in.cameraScale--;
        in.cameraPos = in.cameraPos - Vec2D(300, 160) / (in.cameraScale == 1 ? 1 : 3);
    }
    if (in.inputs.isLeftPressed())
    {
        Vec2D tilePos = (in.mousePos) / (48 * in.cameraScale) - (Vec2D(50, 50) - in.cameraPos) / 48.0f;
        tilePos = Vec2D((int)(tilePos.x), (int)(tilePos.y));
        if (in.buttonSelected == 2)
        {
            if (in.money >= in.selectedTower->getCost())
            {
                in.selectedTower->upgrade();
                in.money -= in.selectedTower->getCost();
                in.selectedTower->setCost(in.selectedTower->getCost() * 2);
            }
        }
        else if (in.buttonSelected == 1)
        {
            std::forward_list<Tower *>::iterator oldT = in.lists.towers.before_begin();
            for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
            {
                if ((*i) == in.selectedTower)
                {
                    Vec2D tmpPos = (*i)->getPosition();
                    in.money += (*i)->getCost() / 2;
                    in.lists.map.removeTowerFromTile(Vec2D((int)(tmpPos.x), (int)(tmpPos.y)));
                    delete (*i);
                    i = in.lists.towers.erase_after(oldT);
                    in.selectedTower = nullptr;
                    break;
                }
                oldT = i;
            }
        }
        else if (in.buttonSelected == 3)
        {
            in.gameState = GAMEPAUSE;
        }
        else if (in.buttonSelected == 4)
        {
            in.gameSpeed *= 2;
            if (in.gameSpeed == 0)
                in.gameSpeed = 1;
        }
        else if (in.buttonSelected == 5)
        {
            in.gameSpeed /= 2;
        }
        if (in.gameSpeed > 16)
            in.gameSpeed = 16;
        if (in.gameSpeed < 1)
            in.gameSpeed = 1;
    }
    if (in.selectedTower == nullptr)
    {
        for (int i = 0; i < 3; i++)
        {
            in.lists.towerHolders.holders[i].update(in.lists.towers, in.lists.map, in.money, in.cameraPos, in.cameraScale);
        }
    }
    if (in.life <= 0)
    {
        in.timeCounter.stop();
        in.gameState = GAMEOVER;
    }
    if (in.wave >= 26)
    {
        in.timeCounter.stop();
        in.lists.saveDatas.timePlayed = in.timeCounter.getTime();
        if (in.currentLevel == in.lists.saveDatas.maxLevel)
            in.lists.saveDatas.maxLevel++;
        in.gameState = VICTORY;
    }
}

void handleGamePause(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            in.gameState = GAMEPLAY;
        }
        else if (in.buttonSelected == 2)
        {
            in.gameState = GAMEOPTION;
        }
        else if (in.buttonSelected == 3)
        {
            in.life = 20;
            in.wave = 0;
            in.money = 20;
            for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
                delete *i;
            for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
                delete *i;
            for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
                delete *i;
            for (std::forward_list<Particle *>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
                delete *i;
            in.lists.enemies.clear();
            in.lists.towers.clear();
            in.lists.missiles.clear();
            in.lists.buffer.clear();
            in.lists.particles.clear();
            for (int i = 0; i < (MAP_HEIGHT * MAP_WIDTH); i++)
                in.lists.map.tilesWithTower[i] = false;
            in.selectedTower = nullptr;

            PlaySound(in.sounds.buttonSound);
            StopMusicStream(in.sounds.gameplayMusic);
            in.timeCounter.stop();
            in.gameState = MENU;
        }
        else if (in.buttonSelected == 4)
        {
            in.life = 20;
            in.wave = 0;
            in.money = 20;
            for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
                delete *i;
            for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
                delete *i;
            for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
                delete *i;
            for (std::forward_list<Particle *>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
                delete *i;
            in.lists.enemies.clear();
            in.lists.towers.clear();
            in.lists.missiles.clear();
            in.lists.buffer.clear();
            in.lists.particles.clear();
            for (int i = 0; i < (MAP_HEIGHT * MAP_WIDTH); i++)
                in.lists.map.tilesWithTower[i] = false;
            in.selectedTower = nullptr;

            PlaySound(in.sounds.buttonSound);
            StopMusicStream(in.sounds.gameplayMusic);
            in.gameState = GAMEPLAY;
        }
    }
}

void handleGameOver(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
                delete *i;
            for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
                delete *i;
            for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
                delete *i;
            for (std::forward_list<Particle *>::iterator i = in.lists.particles.begin(); i != in.lists.particles.end(); i++)
                delete *i;
            in.lists.enemies.clear();
            in.lists.towers.clear();
            in.lists.missiles.clear();
            in.lists.buffer.clear();
            in.lists.particles.clear();
            for (int i = 0; i < (MAP_HEIGHT * MAP_WIDTH); i++)
                in.lists.map.tilesWithTower[i] = false;
            in.selectedTower = nullptr;
            in.gameSpeed = 1;
            PlaySound(in.sounds.buttonSound);
            StopMusicStream(in.sounds.gameplayMusic);
            in.life = 20;
            in.money = 20;
            if (in.difficulty > 3 && in.wave > in.lists.saveDatas.maxWave)
            {
                in.lists.saveDatas.maxWave = in.wave;
                in.gameState = SAVE;
            }
            else
            {
                in.gameState = MENU;
            }
            in.wave = 0;
        }
    }
}

void handleVictory(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        for (std::list<Enemy *>::iterator i = in.lists.enemies.begin(); i != in.lists.enemies.end(); i++)
            delete *i;
        for (std::forward_list<Tower *>::iterator i = in.lists.towers.begin(); i != in.lists.towers.end(); i++)
            delete *i;
        for (std::forward_list<Missile *>::iterator i = in.lists.missiles.begin(); i != in.lists.missiles.end(); i++)
            delete *i;
        in.lists.enemies.clear();
        in.lists.towers.clear();
        in.lists.missiles.clear();
        in.lists.buffer.clear();
        in.lists.particles.clear();
        in.life = 20;
        in.wave = 0;
        in.money = 20;
        for (int i = 0; i < (MAP_HEIGHT * MAP_WIDTH); i++)
            in.lists.map.tilesWithTower[i] = false;
        in.selectedTower = nullptr;
        in.gameSpeed = 1;
        PlaySound(in.sounds.buttonSound);
        for (int i = 0; i < 3; i++)
        {
            loadFile(in.lists.renderDatas[i], i);
        }
        in.gameState = SAVE;
    }
}

void handleEditor(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.holderHovered >= 0 || in.buttonSelected != 0)
            PlaySound(in.sounds.buttonSound);
        if (in.holderHovered >= 0)
        {
            in.holderSelected = in.holderHovered;
        }
        else if (in.buttonSelected == 1)
        {
            std::string path = {"saves/maps/custom/map0.bin"};
            path[21] = in.saveSlot + '0';
            in.lists.map.saveToFile(path.data());
        }
        else if (in.buttonSelected == 2)
        {
            in.lists.map = TileMap();
        }
        else if (in.buttonSelected == 3)
        {
            switch (in.tileRenderType)
            {
            case BORDER:
                in.tileRenderType = DEBUG;
                break;
            case DEBUG:
                in.tileRenderType = NORMAL;
                break;
            case NORMAL:
                in.tileRenderType = EXTENDED;
                break;
            case EXTENDED:
                in.tileRenderType = BORDER;
                break;
            }
        }
        else if (in.buttonSelected == 4)
        {
            in.holderSelected = 0;
            in.tileRenderType = NORMAL;
            in.gameState = MENUPLAY;
        }
        else if (in.buttonSelected == 5)
        {
            in.saveSlot++;
            if (in.saveSlot > 9)
                in.saveSlot = 9;
        }
        else if (in.buttonSelected == 6)
        {
            in.saveSlot--;
            if (in.saveSlot < 0)
                in.saveSlot = 0;
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (in.holderSelected >= 0)
        {
            Vec2D tilePos = (in.mousePos) / (48 * in.cameraScale) - (Vec2D(50, 50) - in.cameraPos) / 48.0f;
            tilePos = Vec2D((int)(tilePos.x), (int)(tilePos.y));
            placeTileAt(in.lists.map, tilePos, in.dragPos, in.lists.tHolders.holders.at(in.holderSelected).tile, in.lists.tHolders.holders.at(in.holderSelected).isDeco);
        }
    }
    if (in.inputs.isRightPressed())
    {
        Vec2D tilePos = (in.mousePos) / (48 * in.cameraScale) - (Vec2D(50, 50) - in.cameraPos) / 48.0f;
        if (tilePos.x > 0 && tilePos.y > 0 && tilePos.x < in.lists.map.getWidth() && tilePos.y < in.lists.map.getHeight())
        {
            in.lists.map.setAltTile(tilePos);
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        in.dragPos = Vec2D(-1, -1);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        in.cameraPos = in.cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y) / in.cameraScale;
    }
    in.cameraScale = cut(GetMouseWheelMove() + in.cameraScale, 1, 3);
}

void handleLoad(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUPLAY;
        }
        else if (in.buttonSelected >= 2 && in.buttonSelected <= 4)
        {
            loadFile(in.lists.saveDatas, in.buttonSelected - 2);
            in.timeCounter.setTime(in.lists.saveDatas.timePlayed);
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUMAP;
        }
    }
}

void handleOption(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENU;
        }
        if (in.buttonSelected == 2)
        {
            PlaySound(in.sounds.buttonSound);
            in.masterVolume = cut(in.masterVolume + 0.05f, 0.0f, 1.0f);
            SetMasterVolume(in.masterVolume);
        }
        if (in.buttonSelected == 3)
        {
            PlaySound(in.sounds.buttonSound);
            in.masterVolume = cut(in.masterVolume - 0.05f, 0.0f, 1.0f);
            SetMasterVolume(in.masterVolume);
        }
        if (in.buttonSelected == 4)
        {
            PlaySound(in.sounds.buttonSound);
            in.effectVolume = cut(in.effectVolume + 0.05f, 0.0f, 1.0f);
            SetSoundVolume(in.sounds.classicTowerSound, 0.4f * in.effectVolume);
            SetSoundVolume(in.sounds.slowTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.explosiveTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.buttonSound, in.effectVolume);
        }
        if (in.buttonSelected == 5)
        {
            PlaySound(in.sounds.buttonSound);
            in.effectVolume = cut(in.effectVolume - 0.05f, 0.0f, 1.0f);
            SetSoundVolume(in.sounds.classicTowerSound, 0.4f * in.effectVolume);
            SetSoundVolume(in.sounds.slowTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.explosiveTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.buttonSound, in.effectVolume);
        }
        if (in.buttonSelected == 6)
        {
            PlaySound(in.sounds.buttonSound);
            in.musicVolume = cut(in.musicVolume + 0.05f, 0.0f, 1.0f);
            SetMusicVolume(in.sounds.gameplayMusic, in.musicVolume);
        }
        if (in.buttonSelected == 7)
        {
            PlaySound(in.sounds.buttonSound);
            in.musicVolume = cut(in.musicVolume - 0.05f, 0.0f, 1.0f);
            SetMusicVolume(in.sounds.gameplayMusic, in.musicVolume);
        }
        if (in.buttonSelected == 8)
        {
            PlaySound(in.sounds.buttonSound);
            if (in.difficulty < (3 + (in.lists.saveDatas.maxLevel == 10)))
                in.difficulty += 1;
        }
        if (in.buttonSelected == 9)
        {
            PlaySound(in.sounds.buttonSound);
            if (in.difficulty > 1)
                in.difficulty -= 1;
        }
    }
}

void handleGameOption(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = GAMEPLAY;
        }
        if (in.buttonSelected == 2)
        {
            PlaySound(in.sounds.buttonSound);
            in.masterVolume = cut(in.masterVolume + 0.05f, 0.0f, 1.0f);
            SetMasterVolume(in.masterVolume);
        }
        if (in.buttonSelected == 3)
        {
            PlaySound(in.sounds.buttonSound);
            in.masterVolume = cut(in.masterVolume - 0.05f, 0.0f, 1.0f);
            SetMasterVolume(in.masterVolume);
        }
        if (in.buttonSelected == 4)
        {
            PlaySound(in.sounds.buttonSound);
            in.effectVolume = cut(in.effectVolume + 0.05f, 0.0f, 1.0f);
            SetSoundVolume(in.sounds.classicTowerSound, 0.4f * in.effectVolume);
            SetSoundVolume(in.sounds.slowTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.explosiveTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.buttonSound, in.effectVolume);
        }
        if (in.buttonSelected == 5)
        {
            PlaySound(in.sounds.buttonSound);
            in.effectVolume = cut(in.effectVolume - 0.05f, 0.0f, 1.0f);
            SetSoundVolume(in.sounds.classicTowerSound, 0.4f * in.effectVolume);
            SetSoundVolume(in.sounds.slowTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.explosiveTowerSound, 0.2f * in.effectVolume);
            SetSoundVolume(in.sounds.buttonSound, in.effectVolume);
        }
        if (in.buttonSelected == 6)
        {
            PlaySound(in.sounds.buttonSound);
            in.musicVolume = cut(in.musicVolume + 0.05f, 0.0f, 1.0f);
            SetMusicVolume(in.sounds.gameplayMusic, in.musicVolume);
        }
        if (in.buttonSelected == 7)
        {
            PlaySound(in.sounds.buttonSound);
            in.musicVolume = cut(in.musicVolume - 0.05f, 0.0f, 1.0f);
            SetSoundVolume(in.sounds.classicTowerSound, 0.4f * in.effectVolume);
            SetMusicVolume(in.sounds.gameplayMusic, in.musicVolume);
        }
    }
}

void handleSave(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENUMAP;
        }
        if (in.buttonSelected >= 2 && in.buttonSelected <= 4)
        {
            PlaySound(in.sounds.buttonSound);
            saveFile(in.lists.saveDatas, in.buttonSelected - 2);
            in.gameState = MENUMAP;
        }
    }
}

void handleCredit(DataHolder &in)
{
    if (in.inputs.isLeftPressed())
    {
        if (in.buttonSelected == 1)
        {
            PlaySound(in.sounds.buttonSound);
            in.gameState = MENU;
        }
    }
}
