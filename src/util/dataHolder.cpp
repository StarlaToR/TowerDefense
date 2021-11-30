#include "dataHolder.hpp"
#include <cstdio>

void DataHolder::unloadDatas()
{
    UnloadTexture(logo);
    UnloadTexture(tileTexture);
}

void DataHolder::handleGameState()
{
    mousePos = Vec2D(GetMousePosition().x,GetMousePosition().y);
    if (gameState == 0)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || framecounter > 360)
        {
            gameState = 1;
        }
    }
    else if (gameState == 1)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            gameState = 2;
        }
    }
    else if (gameState == 2)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vec2D tmpPos = mousePos-Vec2D(50,50);
            if (tmpPos.x > 0 && tmpPos.y > 0 && tmpPos.x <= 48*map.getWidth() && tmpPos.y <= 48*map.getHeight())
            {
                Vec2D tilePos = Vec2D( (int)(tmpPos.x/48), (int)(tmpPos.y/48));
                map.setTileAt(tilePos,(map.getTileAt(tilePos)+1)%19);
            }
            if (buttonSelected == 1) {
                FILE* sv = fopen("assets/maps/default.bin","wb");
                fwrite(&map,1,sizeof(map),sv);
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
    }
    framecounter++;
}