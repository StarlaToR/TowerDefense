#include "render.hpp"
#include <raylib.h>
#include "util/renderUtil.hpp"

void renderMain(DataHolder* in)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (in->gameState == 0)
    {
        renderStartAnim(in);
    }
    else if (in->gameState == 1)
    {
        renderMainMenu(in);
    }
    
    DrawFPS(10, 10);
    EndDrawing();
}

void renderStartAnim(DataHolder* in)
{
    float width = in->screenWidth;
    float heigth = in->screenHeight;
    int frames = in->framecounter;
    if (frames < 180)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,frames*1.66666f,frames*1.6666f},Vector2{150,150},frames*2.0f,getRGB(frames));
    }
    else if (frames < 260)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,getRGB(frames));
    }
    else if (frames < 320)
    {
        DrawTexturePro(in->logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,Fade(getRGB(frames),(320-frames)/60.0f));
    }
}

void renderMainMenu(DataHolder* in) {
    DrawText("Menu", 100,100,30,BLACK);
}