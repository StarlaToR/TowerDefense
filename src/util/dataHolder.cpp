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
    framecounter++;
}