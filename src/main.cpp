#include <raylib.h>
#include "mathHelper.hpp"

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Tower Defense");
    Texture2D logo = LoadTexture("assets/logo_group.png");
    InitAudioDevice();
    


    int anim = 0;
    static float rgb = 0.5;

    // Main game loop
    while (!WindowShouldClose())
    {
        anim++;
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
