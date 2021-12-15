#include "dataHolder.hpp"
#include "../towers/classicTower.hpp"
#include <string>

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
    UnloadTexture(textures.credit);
    UnloadTexture(textures.button);
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
    textures.credit = LoadTexture("assets/textures/credit.png");
    textures.tileTexture = LoadTexture("assets/textures/tileSheet.png");
    textures.button = LoadTexture("assets/textures/button.png");
    textures.gameUI = LoadTexture("assets/textures/ui.png");
    textures.board = LoadTexture("assets/textures/board.png");
    textures.optionButton = LoadTexture("assets/textures/optionButton.png");
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
    selectedTower = nullptr;
    lists.tiles.registerTiles();
    SetMasterVolume(masterVolume);
    lists.towerHolders.initTowers(&sounds.classicTowerSound, &sounds.slowTowerSound, &sounds.explosiveTowerSound);
    timeCounter = TimeCounter();
}

void DataHolder::handleGameState()
{

    if (IsKeyPressed(KEY_RIGHT))
    {
        gameSpeed *= 2;
        if (gameSpeed == 0)
            gameSpeed = 1;
    }
    if (IsKeyPressed(KEY_LEFT))
        gameSpeed /= 2;
    if (gameSpeed > 16)
        gameSpeed = 16;
    if (gameSpeed < 1) gameSpeed = 1;
    inputs.handleInputs();
    UpdateMusicStream(sounds.musicTroll);
    UpdateMusicStream(sounds.gameplayMusic);
    UpdateMusicStream(sounds.introSong);
    if(GetMusicTimePlayed(sounds.musicTroll) >= GetMusicTimeLength(sounds.musicTroll)-0.05f) StopMusicStream(sounds.musicTroll);
    if(GetMusicTimePlayed(sounds.introSong) >= GetMusicTimeLength(sounds.introSong)-0.05f) StopMusicStream(sounds.introSong);
    mousePos = Vec2D(GetMousePosition().x, GetMousePosition().y);

    if (gameState == INTRO)
    {
        if (inputs.isLeftPressed() || framecounter > 360)
        {
            StopMusicStream(sounds.introSong);
            gameState = MENU;
        }
    }
    else if (gameState == MENU)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENUPLAY;
            }
            else if (buttonSelected == 2)
            {
                PlaySound(sounds.buttonSound);
                gameState = OPTION;
            }
            else if (buttonSelected == 3)
            {
                PlaySound(sounds.buttonSound);
                gameState = CREDIT;
            }
            else if (buttonSelected == 4)
            {
                PlaySound(sounds.buttonSound);
                gameState = EXIT;
            }
            else if (buttonSelected == 5)
            {
                PlaySound(sounds.buttonSound);
                if (IsMusicStreamPlaying(sounds.musicTroll))
                {
                    StopMusicStream(sounds.musicTroll);
                }
                else
                {
                    PlayMusicStream(sounds.musicTroll);
                }
            }
            else if (buttonSelected == 6)
            {
                framecounter = 0;
                PlaySound(sounds.buttonSound);
                PlayMusicStream(sounds.introSong);
                gameState = INTRO;
            }
        }
    }
    else if (gameState == MENUPLAY)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                life = 20;
                wave = 0;
                money = 20;
                tileRenderType = NORMAL;
                gameState = MENUMAP;
            }
            if (buttonSelected == 2)
            {
                PlaySound(sounds.buttonSound);
                gameState = LOAD;
            }
            else if (buttonSelected == 3)
            {
                PlaySound(sounds.buttonSound);
                lists.map.loadFromFile("saves/maps/game/default.bin");
                tileRenderType = EXTENDED;
                gameState = EDITOR;
            }
            else if (buttonSelected == 4)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENU;
            }
        }
    }
    else if (gameState == MENUMAP)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected >= 1 && buttonSelected <= 10)
            {
                std::string path = {"saves/maps/game/game0.bin"};
                path[20] = buttonSelected-1 + '0';
                lists.map.loadFromFile(path.data());
                timeCounter.start();
                PlaySound(sounds.buttonSound);
                gameState = GAMEPLAY;
            }
            else if (buttonSelected == 11)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENUPLAY;
            }
            else if (buttonSelected == 12)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENUMAPCUSTOM;
            }
        }
    }
    else if (gameState == MENUMAPCUSTOM)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 11)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENUMAP;
            }
            else
            {
                std::string path = {"saves/maps/custom/map0.bin"};
                path[21] = buttonSelected-1 + '0';
                if (lists.map.loadFromFile(path.data()) >= 0)
                {
                    timeCounter.start();
                    PlaySound(sounds.buttonSound);
                    gameState = GAMEPLAY;
                }
            }
        }
    }
    else if (gameState == OPTION)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENU;
            }
            if (buttonSelected == 2)
            {
                PlaySound(sounds.buttonSound);
                masterVolume = cut(masterVolume + 0.05f, 0.0f, 1.0f);
                SetMasterVolume(masterVolume);
            }
            if (buttonSelected == 3)
            {
                PlaySound(sounds.buttonSound);
                masterVolume = cut(masterVolume - 0.05f, 0.0f, 1.0f);
                SetMasterVolume(masterVolume);
            }
            if (buttonSelected == 4)
            {
                PlaySound(sounds.buttonSound);
                effectVolume = cut(effectVolume + 0.05f, 0.0f, 1.0f);
                SetSoundVolume(sounds.classicTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.slowTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.explosiveTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.buttonSound, 0.4f * effectVolume);
            }
            if (buttonSelected == 5)
            {
                PlaySound(sounds.buttonSound);
                effectVolume = cut(effectVolume - 0.05f, 0.0f, 1.0f);
                SetSoundVolume(sounds.classicTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.slowTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.explosiveTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.buttonSound, 0.4f * effectVolume);
            }
            if (buttonSelected == 6)
            {
                PlaySound(sounds.buttonSound);
                musicVolume = cut(musicVolume + 0.05f, 0.0f, 1.0f);
                SetMusicVolume(sounds.gameplayMusic, 0.4f * musicVolume);
            }
            if (buttonSelected == 7)
            {
                PlaySound(sounds.buttonSound);
                musicVolume = cut(musicVolume - 0.05f, 0.0f, 1.0f);
                SetMusicVolume(sounds.gameplayMusic, 0.4f * musicVolume);
            }
        }
    }
    else if (gameState == GAMEOPTION)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                gameState = GAMEPLAY;
            }
            if (buttonSelected == 2)
            {
                PlaySound(sounds.buttonSound);
                masterVolume = cut(masterVolume + 0.05f, 0.0f, 1.0f);
                SetMasterVolume(masterVolume);
            }
            if (buttonSelected == 3)
            {
                PlaySound(sounds.buttonSound);
                masterVolume = cut(masterVolume - 0.05f, 0.0f, 1.0f);
                SetMasterVolume(masterVolume);
            }
            if (buttonSelected == 4)
            {
                PlaySound(sounds.buttonSound);
                effectVolume = cut(effectVolume + 0.05f, 0.0f, 1.0f);
                SetSoundVolume(sounds.classicTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.slowTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.explosiveTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.buttonSound, 0.4f * effectVolume);
            }
            if (buttonSelected == 5)
            {
                PlaySound(sounds.buttonSound);
                effectVolume = cut(effectVolume - 0.05f, 0.0f, 1.0f);
                SetSoundVolume(sounds.classicTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.slowTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.explosiveTowerSound, 0.4f * effectVolume);
                SetSoundVolume(sounds.buttonSound, 0.4f * effectVolume);
            }
            if (buttonSelected == 6)
            {
                PlaySound(sounds.buttonSound);
                musicVolume = cut(musicVolume + 0.05f, 0.0f, 1.0f);
                SetMusicVolume(sounds.gameplayMusic, 0.4f * musicVolume);
            }
            if (buttonSelected == 7)
            {
                PlaySound(sounds.buttonSound);
                musicVolume = cut(musicVolume - 0.05f, 0.0f, 1.0f);
                SetMusicVolume(sounds.gameplayMusic, 0.4f * musicVolume);
            }
            
        }
    }
    else if (gameState == CREDIT)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                gameState = MENU;
            }
        }
    }
    else if (gameState == LOAD)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                tileRenderType = NORMAL;
                gameState = GAMEPLAY;
            }
            else if (buttonSelected >= 2 && buttonSelected <= 4)
            {
                loadFile(lists.saveDatas,buttonSelected-2);
                std::string path = {"saves/maps/game/game0.bin"};
                path[20] = lists.saveDatas.maxLevel + '0';
                lists.map.loadFromFile(path.data());
                timeCounter.setTime(lists.saveDatas.timePlayed);
                timeCounter.start();
                PlaySound(sounds.buttonSound);
                gameState = GAMEPLAY;
            }
        }
    }
    else if (gameState == GAMEPLAY)
    {
        if (!onPause)
        {
            PlayMusicStream(sounds.gameplayMusic);
            int counter = 0;
            while (counter < gameSpeed)
            {
                handleEnemiesBuffer(lists.map, lists.enemies, lists.buffer, wave);
                selectedTower = handleTowers(lists.towers, lists.enemies, lists.missiles, lists.particles, selectedTower, cameraPos, cameraScale); 
                handleMissiles(lists.missiles, lists.enemies, lists.particles);
                handleEnemies(lists.map, money, lists.enemies, lists.particles, life);
                handleParticles(lists.particles);
                counter++;
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                cameraPos = cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y) / cameraScale;
            }
            if (GetMouseWheelMove() > 0.1 && cameraScale < 3)
            {
                cameraScale++;
                cameraPos = cameraPos + Vec2D(300, 160) / (cameraScale == 2 ? 1 : 3);
            }
            if (GetMouseWheelMove() < -0.1 && cameraScale > 1)
            {
                cameraScale--;
                cameraPos = cameraPos - Vec2D(300, 160) / (cameraScale == 1 ? 1 : 3);
            }
            if (inputs.isLeftPressed())
            {
                Vec2D tilePos = (mousePos) / (48 * cameraScale) - (Vec2D(50, 50) - cameraPos) / 48.0f;
                tilePos = Vec2D((int)(tilePos.x), (int)(tilePos.y));
                if (buttonSelected == 2)
                {
                    if (money >= selectedTower->getCost())
                    {
                        selectedTower->upgrade();
                        money -= selectedTower->getCost();
                        selectedTower->setCost(selectedTower->getCost() * 2);
                    }
                }
                else if (buttonSelected == 1)
                {
                    std::forward_list<Tower *>::iterator oldT = lists.towers.before_begin();
                    for (std::forward_list<Tower *>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++)
                    {
                        if ((*i) == selectedTower)
                        {
                            Vec2D tmpPos = (*i)->getPosition();
                            money += (*i)->getCost() * (*i)->getLevel() / 4;
                            lists.map.removeTowerFromTile(Vec2D((int)(tmpPos.x),(int)(tmpPos.y)));
                            delete(*i);
                            i = lists.towers.erase_after(oldT);
                            selectedTower = nullptr;
                            break;
                        }
                        oldT = i;
                    }
                }
                else if(buttonSelected == 3)
                {
                    onPause = true;
                }
            }
            if (selectedTower == nullptr)
            {
                for (int i = 0; i < 3; i++)
                {
                    lists.towerHolders.holders[i].update(lists.towers, lists.map, money, cameraPos, cameraScale);
                }
            }
            if (life <= 0)
            {
                timeCounter.stop();
                gameState = GAMEOVER;
            }
            if(wave >= 26)
            {
                timeCounter.stop();
                gameState = VICTORY;
            }
        }
        else
        {
            gameSpeed = 0;
            if (inputs.isLeftPressed())
            {
                if (buttonSelected == 1)
                {
                    onPause = false;
                    gameSpeed = 1;
                }
                else if (buttonSelected == 2)
                {
                    gameState = GAMEOPTION;
                }
                else if (buttonSelected == 3)
                {
                    onPause = false;
                    for (std::list<Enemy*>::iterator i = lists.enemies.begin(); i != lists.enemies.end(); i++) delete *i;
                    for (std::forward_list<Tower*>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++) delete *i;
                    for (std::forward_list<Missile*>::iterator i = lists.missiles.begin(); i != lists.missiles.end(); i++) delete *i;
                    for (std::forward_list<Particle *>::iterator i = lists.particles.begin(); i != lists.particles.end(); i++) delete *i;
                    lists.enemies.clear();
                    lists.towers.clear();
                    lists.missiles.clear();
                    lists.buffer.clear();
                    lists.particles.clear();
                    for (int i = 0; i < (MAP_HEIGHT*MAP_WIDTH); i++) lists.map.tilesWithTower[i] = false;
                    selectedTower = nullptr;
                    gameSpeed = 1;

                    PlaySound(sounds.buttonSound);
                    StopMusicStream(sounds.gameplayMusic);
                    gameState = MENU;
                }
            }
        }
    }
    else if (gameState == SAVE)
    {
        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                PlaySound(sounds.buttonSound);
                tileRenderType = NORMAL;
                gameState = MENUMAP;
            }
            if (buttonSelected >= 2 && buttonSelected <= 4)
            {
                saveFile(lists.saveDatas, buttonSelected-2);
            }
        }
    }
    else if (gameState == GAMEOVER)
    {

        if (inputs.isLeftPressed())
        {
            if (buttonSelected == 1)
            {
                for (std::list<Enemy*>::iterator i = lists.enemies.begin(); i != lists.enemies.end(); i++) delete *i;
                for (std::forward_list<Tower*>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++) delete *i;
                for (std::forward_list<Missile*>::iterator i = lists.missiles.begin(); i != lists.missiles.end(); i++) delete *i;
                for (std::forward_list<Particle *>::iterator i = lists.particles.begin(); i != lists.particles.end(); i++) delete *i;
                lists.enemies.clear();
                lists.towers.clear();
                lists.missiles.clear();
                lists.buffer.clear();
                lists.particles.clear();
                for (int i = 0; i < (MAP_HEIGHT*MAP_WIDTH); i++) lists.map.tilesWithTower[i] = false;
                selectedTower = nullptr;
                gameSpeed = 1;

                PlaySound(sounds.buttonSound);
                StopMusicStream(sounds.gameplayMusic);
                gameState = MENU;
            }
        }
    }
    else if (gameState == VICTORY)
    {
        
        if (inputs.isLeftPressed())
        {
            for (std::list<Enemy*>::iterator i = lists.enemies.begin(); i != lists.enemies.end(); i++) delete *i;
            for (std::forward_list<Tower*>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++) delete *i;
            for (std::forward_list<Missile*>::iterator i = lists.missiles.begin(); i != lists.missiles.end(); i++) delete *i;
            lists.enemies.clear();
            lists.towers.clear();
            lists.missiles.clear();
            lists.buffer.clear();
            lists.particles.clear();
            for (int i = 0; i < (MAP_HEIGHT*MAP_WIDTH); i++) lists.map.tilesWithTower[i] = false;
            selectedTower = nullptr;
            gameSpeed = 1;
            PlaySound(sounds.buttonSound);
            gameState = MENU;
        }
    }
    else if (gameState == EDITOR)
    {
        if (inputs.isLeftPressed())
        {
            if (holderHovered >= 0 || buttonSelected != 0) PlaySound(sounds.buttonSound);
            if (holderHovered >= 0)
            {
                holderSelected = holderHovered;
            }
            else if (buttonSelected == 1)
            {
                std::string path = {"saves/maps/custom/map0.bin"};
                path[21] = saveSlot + '0';
                lists.map.saveToFile(path.data());
            }
            else if (buttonSelected == 2)
            {
                lists.map = TileMap();
            }
            else if (buttonSelected == 3)
            {
                switch (tileRenderType)
                {
                case BORDER:
                    tileRenderType = DEBUG;
                    break;
                case DEBUG:
                    tileRenderType = NORMAL;
                    break;
                case NORMAL:
                    tileRenderType = EXTENDED;
                    break;
                case EXTENDED:
                    tileRenderType = BORDER;
                    break;
                }
            }
            else if (buttonSelected == 4) 
            {
                holderSelected = 0;
                gameState = MENU;
            }
            else if (buttonSelected == 5) 
            {
                saveSlot++;
                if (saveSlot > 9) saveSlot = 9;
            }
            else if (buttonSelected == 6) 
            {
                saveSlot--;
                if (saveSlot < 0) saveSlot = 0;
            }
            
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (holderSelected >= 0)
            {
                Vec2D tilePos = (mousePos) / (48 * cameraScale) - (Vec2D(50, 50) - cameraPos) / 48.0f;
                tilePos = Vec2D((int)(tilePos.x), (int)(tilePos.y));
                placeTileAt(lists.map, tilePos, dragPos, lists.tHolders.holders.at(holderSelected).tile, lists.tHolders.holders.at(holderSelected).isDeco);
            }
        }
        if (inputs.isRightPressed())
        {
            Vec2D tilePos = (mousePos) / (48 * cameraScale) - (Vec2D(50, 50) - cameraPos) / 48.0f;
            if (tilePos.x > 0 && tilePos.y > 0 && tilePos.x < lists.map.getWidth() && tilePos.y < lists.map.getHeight())
            {
                lists.map.setAltTile(tilePos);
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            dragPos = Vec2D(-1, -1);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            cameraPos = cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y) / cameraScale;
        }
        cameraScale = cut(GetMouseWheelMove() + cameraScale, 1, 3);
    }
    framecounter++;
}
