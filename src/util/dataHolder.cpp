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
    UnloadMusicStream(music);
}

void DataHolder::handleGameState()
{
    mousePos = Vec2D(GetMousePosition().x, GetMousePosition().y);
    if (gameState == INTRO)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || framecounter > 360)
        {
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
                PlayMusicStream(music);
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
                gameState = GAMEPLAY;
            }
            else if (buttonSelected == 2) 
            {
                PlaySound(buttonSound);
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
                gameState = GAMEPLAY;
            }
            
        }
    }
    else if (gameState == EDITOR)
    {
        handleTowers(&towers, &enemies, &missiles);
        handleMissiles(&missiles, &enemies, &particles);
        handleEnemies(&map, &money, &enemies, &particles);
        handleParticles(&particles);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (buttonSelected == 1)
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
            Vec2D tmpPos = mousePos - Vec2D(50, 50);
            if (tmpPos.x > 0 && tmpPos.y > 0 && tmpPos.x <= 48 * map.getWidth() && tmpPos.y <= 48 * map.getHeight())
            {
                Vec2D tilePos = Vec2D((int)(tmpPos.x / 48), (int)(tmpPos.y / 48));
                if (dragPos.x > -0.9f && (tilePos - dragPos).lengthSquared() < 1.1 && (tilePos - dragPos).lengthSquared() > 0.9)
                {
                    map.drawRoad(dragPos, Direction(tilePos - dragPos));
                }
                dragPos = tilePos;
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vec2D tmpPos = mousePos - Vec2D(50, 50);
            if (tmpPos.x > 0 && tmpPos.y > 0 && tmpPos.x <= 48 * map.getWidth() && tmpPos.y <= 48 * map.getHeight())
            {
                Vec2D tilePos = Vec2D((int)(tmpPos.x / 48), (int)(tmpPos.y / 48));
                map.setAltTile(tilePos);
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            dragPos = Vec2D(-1, -1);
    }
    framecounter++;
}
