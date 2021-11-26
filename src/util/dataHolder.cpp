#include "dataHolder.hpp"

void DataHolder::unloadDatas()
{
    UnloadTexture(logo);
}

void DataHolder::handleGameState()
{
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
        Vec2D mousePos = Vec2D(GetMousePosition().x,GetMousePosition().y)-Vec2D(50,50);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (mousePos.x > 0 && mousePos.y > 0 && mousePos.x <= 48*map.getWidth() && mousePos.y <= 48*map.getHeight())
            {
                Vec2D tilePos = Vec2D( (int)(mousePos.x/48), (int)(mousePos.y/48));
                map.setTileAt(tilePos,map.getTileAt(tilePos)+1);
            }
        }
    }
    framecounter++;
}