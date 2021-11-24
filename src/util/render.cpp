#include "render.hpp"
#include <raylib.h>

void renderMain() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    rgb = mod(rgb+0.013f, 0.0f, 1.0f);
    if (anim < 180)
    {
        DrawTexturePro(logo,Rectangle{0,0,300,300},Rectangle{screenWidth/2,screenHeight/2,anim*1.66666f,anim*1.6666f},Vector2{150,150},anim*2.0f,ColorFromHSV(rgb*360.0f,0.5,1.0));
    }
    else if (anim < 300)
    {
        DrawTexturePro(logo,Rectangle{0,0,300,300},Rectangle{screenWidth/2,screenHeight/2,300,300},Vector2{150,150},0,ColorFromHSV(rgb*360.0f,0.5,1.0));
    }
    else if (anim < 360)
    {
        DrawTexturePro(logo,Rectangle{0,0,300,300},Rectangle{screenWidth/2,screenHeight/2,300,300},Vector2{150,150},0,Fade(ColorFromHSV(rgb*360.0f,0.5,1.0),(360-anim)/60.0f));
    }
    
    DrawFPS(10, 10);
    EndDrawing();
}

void renderStartAnim()
{

}