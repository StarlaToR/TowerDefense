#include "dataHolder.hpp"
#include <cstdio>

void DataHolder::unloadDatas()
{
    for (std::forward_list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); i++) delete *i;
    for (std::forward_list<Tower*>::iterator i = towers.begin(); i != towers.end(); i++) delete *i;
    for (std::forward_list<Missile*>::iterator i = missiles.begin(); i != missiles.end(); i++) delete *i;
    UnloadTexture(logo);
    UnloadTexture(tileTexture);
    UnloadTexture(background);
    UnloadTexture(title);
    UnloadTexture(credit);
    UnloadTexture(button);
    UnloadFont(fontButton);
    UnloadFont(fontTitle);
    UnloadSound(buttonSound);
    UnloadMusicStream(musicTroll);
    UnloadMusicStream(gameplayMusic);
}

void DataHolder::handleGameState()
{
    mousePos = Vec2D(GetMousePosition().x, GetMousePosition().y);
    if (gameState == INTRO)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || framecounter > 360)
        {
            StopMusicStream(introSong);
            gameState = MENU;
        }
    }
    else if (gameState == MENU)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1) 
            {
                PlaySound(buttonSound);
                gameState = MENUPLAY;
            }
            else if (buttonSelected == 2) 
            {
                PlaySound(buttonSound);
                gameState = OPTION;
            }
            else if (buttonSelected == 3) 
            {
                PlaySound(buttonSound);
                gameState = CREDIT;
            }
            else if (buttonSelected == 4) 
            {
                PlaySound(buttonSound);
                gameState = EXIT;
            }
            else if (buttonSelected == 5) 
            {
                PlaySound(buttonSound);
                PlayMusicStream(musicTroll);
            }
            else if (buttonSelected == 6) 
            {
                framecounter = 0;
                PlaySound(buttonSound);
                gameState = INTRO;
            }
            
            
        }
    }
    else if (gameState == MENUPLAY)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1) 
            {
                PlaySound(buttonSound);
                tileRenderType = NORMAL;
                gameState = GAMEPLAY;
            }
            else if (buttonSelected == 2) 
            {
                PlaySound(buttonSound);
                tileRenderType = EXTENDED;
                gameState = EDITOR;
            }
            else if (buttonSelected == 3) 
            {
                PlaySound(buttonSound);
                gameState = MENU;
            }
            
        }
    }
    else if (gameState == OPTION)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1) 
            {
                PlaySound(buttonSound);
                gameState = MENU;
            }
            
        }
    }
    else if (gameState == CREDIT)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1) 
            {
                PlaySound(buttonSound);
                gameState = MENU;
            }
            
        }
    }
    else if (gameState == LOAD)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1) 
            {
                PlaySound(buttonSound);
                tileRenderType = NORMAL;
                gameState = GAMEPLAY;
            }
            
        }
    }
    else if (gameState == GAMEPLAY)
    {
        PlayMusicStream(gameplayMusic);
        handleEnemiesBuffer(&map, &enemies, &buffer, wave);
        selectedTower = handleTowers(&towers, &enemies, &missiles, selectedTower); 
        handleMissiles(&missiles, &enemies, &particles);
        handleEnemies(&map, &money, &enemies, &particles);
        handleParticles(&particles);
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            cameraPos = cameraPos - Vec2D(GetMouseDelta().x, GetMouseDelta().y)/cameraScale;
        }
        cameraScale = cut(GetMouseWheelMove()+cameraScale,1,3);
    }
    else if (gameState == EDITOR)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (holderHovered >= 0)
            {
                holderSelected = holderHovered;
            }
            else if (buttonSelected == 1)
            {
                FILE *sv = fopen("assets/maps/default.bin", "wb");
                fwrite(&map, 1, sizeof(map), sv);
                fclose(sv);
            }
            else if (buttonSelected == 2)
            {
                map = TileMap();
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
                placeTileAt(&map,tilePos,&dragPos,tHolders.holders.at(holderSelected).tile, tHolders.holders.at(holderSelected).isDeco);
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vec2D tilePos = (mousePos) / (48*cameraScale) - (Vec2D(50, 50)-cameraPos)/48.0f;
            if (tilePos.x > 0 && tilePos.y > 0 && tilePos.x < map.getWidth() && tilePos.y < map.getHeight())
            {
                map.setAltTile(tilePos);
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
