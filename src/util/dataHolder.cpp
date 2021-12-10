#include "dataHolder.hpp"
#include "../towers/classicTower.hpp"

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
    for (std::list<Enemy*>::iterator i = lists.enemies.begin(); i != lists.enemies.end(); i++) delete *i;
    for (std::forward_list<Tower*>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++) delete *i;
    for (std::forward_list<Missile*>::iterator i = lists.missiles.begin(); i != lists.missiles.end(); i++) delete *i;
    UnloadTexture(textures.logo);
    UnloadTexture(textures.tileTexture);
    UnloadTexture(textures.background);
    UnloadTexture(textures.title);
    UnloadTexture(textures.credit);
    UnloadTexture(textures.button);
    UnloadTexture(textures.marie_antoine);
    UnloadTexture(textures.logoIsart);
    UnloadTexture(textures.gameUI);
    UnloadFont(fontButton);
    UnloadFont(fontTitle);
    UnloadSound(sounds.buttonSound);
    UnloadMusicStream(sounds.musicTroll);
    UnloadMusicStream(sounds.introSong);
    UnloadMusicStream(sounds.gameplayMusic);
}

void DataHolder::initDatas()
{
    textures.logo = LoadTexture("assets/textures/logo.png");
    textures.logoIsart = LoadTexture("assets/textures/logo_isart.png");
    textures.marie_antoine = LoadTexture("assets/textures/Marie-Antoine.png");
    textures.background = LoadTexture("assets/textures/background.png");
    textures.title = LoadTexture("assets/textures/title.png");
    textures.credit = LoadTexture("assets/textures/credit.png");
    textures.tileTexture = LoadTexture("assets/textures/tileSheet.png");
    textures.button = LoadTexture("assets/textures/button.png");
    textures.gameUI = LoadTexture("assets/textures/ui.png");
    sounds.buttonSound = LoadSound("assets/sounds/button.ogg");
    sounds.musicTroll = LoadMusicStream("assets/sounds/ouioui.ogg");
    sounds.gameplayMusic = LoadMusicStream("assets/sounds/gameplayMusic.ogg");
    sounds.introSong = LoadMusicStream("assets/sounds/introSong.ogg");
    fontButton = LoadFontEx("assets/font/ethnocentric.ttf", 100, 0, 0);
    fontTitle = LoadFontEx("assets/font/godofwar.ttf", 100, 0, 0);
    lists.map = TileMap();
    SetMusicVolume(sounds.musicTroll, 0.15f);
    selectedTower = nullptr;
    lists.map.loadFromFile("saves/maps/default.bin");
    lists.tiles.registerTiles();
    SetMasterVolume(masterVolume);
}

void DataHolder::handleGameState()
{

    if (IsKeyPressed(KEY_RIGHT))
    {
        gameSpeed *= 2;
        if (gameSpeed == 0) gameSpeed = 1;
    }
    if (IsKeyPressed(KEY_LEFT)) gameSpeed /= 2;
    if (gameSpeed > 16) gameSpeed = 16;
    //if (gameSpeed < 1) gameSpeed = 1;
    inputs.handleInputs();
    UpdateMusicStream(sounds.musicTroll);
    UpdateMusicStream(sounds.gameplayMusic);
    UpdateMusicStream(sounds.introSong);
    if(timePlayed >= 16.0f) StopMusicStream(sounds.musicTroll);
    timePlayed = GetMusicTimePlayed(sounds.musicTroll);
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
                PlayMusicStream(sounds.musicTroll);
            }
            else if (buttonSelected == 6) 
            {
                framecounter = 0;
                PlaySound(sounds.buttonSound);
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
                tileRenderType = NORMAL;
                gameState = GAMEPLAY;
            }
            if (buttonSelected == 2)
            {
                PlaySound(sounds.buttonSound);
                gameState = LOAD;
            }
            else if (buttonSelected == 3) 
            {
                PlaySound(sounds.buttonSound);
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
                masterVolume = cut(masterVolume+0.05f,0.0f,1.0f);
                SetMasterVolume(masterVolume);
            }
            if (buttonSelected == 3) 
            {
                PlaySound(sounds.buttonSound);
                masterVolume = cut(masterVolume-0.05f,0.0f,1.0f);
                SetMasterVolume(masterVolume);
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
        }
    }
    else if (gameState == GAMEPLAY)
    {
        PlayMusicStream(sounds.gameplayMusic);
        int tmp = 0;
        if (gameSpeed == 0 && IsKeyPressed(KEY_UP)) tmp = -1;
        while (tmp < gameSpeed)
        {
            handleEnemiesBuffer(lists.map, lists.enemies, lists.buffer, wave);
            selectedTower = handleTowers(lists.towers, lists.enemies, lists.missiles, selectedTower, cameraPos, cameraScale); 
            handleMissiles(lists.missiles, lists.enemies, lists.particles);
            handleEnemies(lists.map, money, lists.enemies, lists.particles, life);
            handleParticles(lists.particles);
            tmp++;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            cameraPos = cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y)/cameraScale;
        }
        if (GetMouseWheelMove() > 0.1 && cameraScale < 3)
        {
            cameraScale++;
            cameraPos = cameraPos + Vec2D(300,160) / (cameraScale == 2 ? 1 : 3);
        }
        if (GetMouseWheelMove() < -0.1 && cameraScale > 1)
        {
            cameraScale--;
            cameraPos = cameraPos - Vec2D(300,160) / (cameraScale == 1 ? 1 : 3);
        }
        if (inputs.isLeftPressed())
        {
            Vec2D tilePos = (mousePos) / (48*cameraScale) - (Vec2D(50, 50)-cameraPos)/48.0f;
            tilePos = Vec2D((int)(tilePos.x),(int)(tilePos.y));
            if (mousePos.x > 50 && mousePos.y > 50 && mousePos.x < 1202 && mousePos.y < 626 && tilePos.x >= 0 && tilePos.y >= 0 && tilePos.x < lists.map.getWidth() && tilePos.y < lists.map.getHeight())
            {
                if (selectedTower == nullptr && !lists.map.isRoad(lists.map.getTileAt(tilePos)) && lists.map.getTileAt(tilePos,true) == UNDEFINED && !lists.map.isTileWithTower(tilePos))
                {
                    lists.towers.push_front(new ClassicTower(tilePos));
                    lists.map.setTileWithTower(tilePos);
                }
            }
            if (buttonSelected == 2)
            {
                if(money >= selectedTower->getCost())
                {
                    selectedTower->upgrade();
                    money -= selectedTower->getCost();
                }
            }
            else if (buttonSelected == 1)
            {
                std::forward_list<Tower*>::iterator oldT = lists.towers.before_begin();
                for (std::forward_list<Tower*>::iterator i = lists.towers.begin(); i != lists.towers.end(); i++)
                {
                    if((*i) == selectedTower)
                    {
                        Vec2D tmpPos = (*i)->getPosition();
                        money += (*i)->getCost() * (*i)->getLevel() / 2;
                        lists.map.removeTowerFromTile(Vec2D((int)(tmpPos.x),(int)(tmpPos.y)));
                        delete(*i);
                        i = lists.towers.erase_after(oldT);
                        selectedTower = nullptr;
                        break;
                    }
                    oldT = i;
                }
            }
        }
        if(selectedTower == nullptr)
        {
            for (int i = 0; i < 3; i++)
            {
                lists.towerHolders.holders[i].update(lists.towers, lists.map, money, cameraPos, cameraScale);
            }
        }
    }
    else if (gameState == EDITOR)
    {
        if (inputs.isLeftPressed())
        {
            if (holderHovered >= 0)
            {
                holderSelected = holderHovered;
            }
            else if (buttonSelected == 1)
            {
                lists.map.saveToFile("saves/maps/default.bin");
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
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (holderSelected >= 0)
            {
                Vec2D tilePos = (mousePos) / (48*cameraScale) - (Vec2D(50, 50)-cameraPos)/48.0f;
                tilePos = Vec2D((int)(tilePos.x),(int)(tilePos.y));
                placeTileAt(lists.map,tilePos,dragPos,lists.tHolders.holders.at(holderSelected).tile, lists.tHolders.holders.at(holderSelected).isDeco);
            }
        }
        if (inputs.isRightPressed())
        {
            Vec2D tilePos = (mousePos) / (48*cameraScale) - (Vec2D(50, 50)-cameraPos)/48.0f;
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
            cameraPos = cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y)/cameraScale;
        }
        cameraScale = cut(GetMouseWheelMove()+cameraScale,1,3);
    }
    framecounter++;
}
