#define VEC2_TO_RAYLIB_VECTOR2                                       \
    Vec2D(const Vector2& f) { x = f.x; y = f.y; }                        \
    operator Vector2() const { return Vector2{x,y}; }

#include "render.hpp"
#include <raylib.h>
#include "util/renderUtil.hpp"

const char* difficultyString[4] = {"             Easy", "           Medium","             Hard", "       NIGHTMARE"};

void renderMain(DataHolder& in) 
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (in.gameState)
    {
    case INTRO:
        renderStartAnim(in);
        break;
    case MENU:
        renderMainMenu(in);
        menuMain(in);
        break;
    case MENUPLAY:
        renderPlay(in);
        break;
    case EDITOR:
        renderEditor(in);
        break;
    case GAMEPLAY:
        renderGameplay(in);
        break;
    case LOAD:
        renderLoad(in);
        break;
    case SAVE:
        renderSave(in);
        break;
    case MENUMAP:
        renderMenuMap(in);
        break;
    case MENUMAPCUSTOM:
        renderMenuMapCustom(in);
        break;
    case GAMEOVER:
        renderGameOver(in);
        break;
    case VICTORY:
        renderVictory(in);
        break;
    case OPTION:
        renderOption(in);
        break;
    case GAMEOPTION:
        renderGameOption(in);
        break;
    case CREDIT:
        renderCredit(in);
        break;
    case EXIT:
        in.closeWindow = true;
        break;
    default:
        break;
    }
    DrawFPS(10, 10);
    EndDrawing();
}

void renderStartAnim(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    size_t frames = in.framecounter;
    if (frames < 180)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,frames*1.66666f,frames*1.6666f},Vector2{150,150},frames*2.0f,getRGB(frames));
    }
    else if (frames < 260)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,getRGB(frames));
    }
    else if (frames < 320)
    {
        DrawTexturePro(in.textures.logo,Rectangle{0,0,300,300},Rectangle{width/2,heigth/2,300,300},Vector2{150,150},0,Fade(getRGB(frames),(320-frames)/60.0f));
    }
}

void renderMainMenu(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{(float)(in.framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.logo, Rectangle{0,0,300,300},Rectangle{width, heigth,100,100},Vector2{100,100}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Tower Defense", Vector2{480,27},70,4,BLACK);
    
}

void renderGameOver(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{(float)(in.framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.board, Rectangle{0,0,720,900},Rectangle{680, 350,500,500},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Game Over", Vector2{560,27},70,4,BLACK);
    DrawTextEx(in.fontButton, TextFormat("Wave : %d",in.wave),Vector2{650,450},40,0, BLACK);
    if (in.difficulty > 3 && in.wave > in.lists.saveDatas.maxWave) DrawText("New High Score!",650,500,20,getRGB(in.framecounter));
    if (in.difficulty < 3)
    {
        DrawTextEx(in.fontButton, "You noob,",Vector2{650,300},40,0, BLACK);
        DrawTextEx(in.fontButton, "Try again",Vector2{650,350},40,0, BLACK);
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }

}

void renderVictory(DataHolder& in)
{
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{(float)(in.framecounter/3.0f),0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.board, Rectangle{0,0,720,900},Rectangle{680, 350,500,500},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Victory", Vector2{560,27},70,4,BLACK);
    DrawTextEx(in.fontButton, TextFormat("Wave : %d",in.wave-1),Vector2{650,450},40,0, BLACK);
    if (drawButtonMenu(in, "Continue", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
}

void renderEditor(DataHolder& in)
{
    drawMapElements(in, true);
    in.buttonSelected = 0;
    in.holderHovered = -1;
    if (drawButton(in, "Save Map", Vec2D(1300,570),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButton(in, "Clear Map", Vec2D(1300,670),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButton(in, "Change view", Vec2D(1300,770),Vec2D(200,50), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButton(in, "Back", Vec2D(150, 730),Vec2D(250,70), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    DrawRectangleRounded(toRayLibRectangle(Vec2D(600,740),Vec2D(250,50)),0.2,10,LIGHTGRAY);
    DrawRectangleRoundedLines(toRayLibRectangle(Vec2D(600,740),Vec2D(250,50)),0.2,10,2,BLACK);
    DrawText(TextFormat("Save slot: %d",in.saveSlot+1),610,755,30,BLACK);
    if (drawButton(in, "+", Vec2D(900, 740), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 5;
    }
    if (drawButton(in, "-", Vec2D(1000, 740), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 6;
    }
    DrawText("Terrain", 1300, 70, 20, BLACK);
    DrawText("Road element", 1300, 200, 20, BLACK);
    DrawText("Decoration", 1300, 380, 20, BLACK);
    for (unsigned int i = 0; i < in.lists.tHolders.holders.size(); i++)
    {
        TileHolder* tmp = &in.lists.tHolders.holders.at(i);
        Vec2D screenPos = tmp->position*Vec2D(64,64)+Vec2D(1300,100);
        DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tmp->getTile()),toRayLibRectangle(screenPos,Vec2D(48,48)),Vec2D(),0,WHITE);
        if (in.mousePos.x > screenPos.x && in.mousePos.y > screenPos.y && in.mousePos.x < screenPos.x + 48 && in.mousePos.y < screenPos.y + 48)
        {
            in.holderHovered = i;
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,BLUE);
        }
        else if (in.holderSelected == (int)(i))
        {
            DrawRectangleLinesEx(toRayLibRectangle(screenPos,Vec2D(48,48)),2,RED);
        }
    }
}

void renderGameplay(DataHolder& in)
{
    Vec2D mTilePos = (in.mousePos) / (48*in.cameraScale) - (Vec2D(50, 50)-in.cameraPos)/48.0f;
    mTilePos = Vec2D((int)(mTilePos.x),(int)(mTilePos.y));
    drawMapElements(in, false);
    in.buttonSelected = 0;
    DrawTextEx(in.fontButton, TextFormat("Money : %d",in.money),Vec2D(1330,40),30,0,BLACK);
    DrawTextEx(in.fontButton,TextFormat("Wave : %d",in.wave),Vec2D(1350,90),30,0,BLACK);
    DrawRectangleRec(toRayLibRectangle(Vec2D(50,750),Vec2D(1156,74)),BLACK);
    DrawRectangleRec(toRayLibRectangle(Vec2D(52,752),Vec2D(1152,70)),RED);
    DrawRectangleRec(toRayLibRectangle(Vec2D(52,752),Vec2D(57.6 * in.life,70)),GREEN);
    if (in.onPause)
    {
        if (drawButtonMenu(in, "Resume", Vec2D(657,150), Vec2D(650, 100),Vec2D(270,150), in.mousePos))
        {
            in.buttonSelected = 1;
        }
        if (drawButtonMenu(in, "Option",  Vec2D(670,450), Vec2D(650, 400),Vec2D(270,150), in.mousePos))
        {
            in.buttonSelected = 2;
        }
        if (drawButtonMenu(in, "Menu", Vec2D(700, 630), Vec2D(650, 580),Vec2D(270,150), in.mousePos))
        {
            in.buttonSelected = 3;
        }
        if (drawButtonMenu(in, "Restart", Vec2D(638, 300), Vec2D(620, 250),Vec2D(320,150), in.mousePos))
        {
            in.buttonSelected = 4;
        }
    }
    else
    {
        DrawTexturePro(in.textures.buttonPause, Rectangle{0,0,300,300}, Rectangle{1400,750,150,150}, Vector2{50,50},0,WHITE);
        DrawTexturePro(in.textures.buttonAccelerateSpeed, Rectangle{0,0,300,300}, Rectangle{750,715,100,100}, Vector2{50,50},0,WHITE);
        DrawTexturePro(in.textures.buttonSlowSpeed, Rectangle{0,0,300,300}, Rectangle{500,715,100,100}, Vector2{50,50},0,WHITE);
        DrawTexturePro(in.textures.speedCounter, Rectangle{0,0,300,300}, Rectangle{625,715,100,100}, Vector2{50,50},0,WHITE);
        DrawTextEx(in.fontButton, TextFormat("%d", in.gameSpeed), Vec2D(602, 700), 40, 0, BLACK);
        drawTowerUpgradeMenu(in, in.buttonSelected);
        for (int i = 0; i < 3; i++)
        {
            TowerHolder* tmpHolder = &in.lists.towerHolders.holders[i];
            if (tmpHolder->isUsed)
            {
                bool valid = (in.mousePos.x > 50 && in.mousePos.y > 50 && in.mousePos.x < 1202 && in.mousePos.y < 626 && !in.lists.map.isRoad(in.lists.map.getTileAt(mTilePos))
                && in.lists.map.getTileAt(mTilePos,true) == UNDEFINED && !in.lists.map.isTileWithTower(mTilePos));
                DrawCircleV(in.mousePos, tmpHolder->getRange()*48*in.cameraScale,Fade(valid ? GREEN : RED,0.3f));
                DrawTexturePro(in.textures.tileTexture,in.lists.tiles.tileCrops.at(tmpHolder->getTexture()),toRayLibRectangle(in.mousePos,Vec2D(80,80)),Vec2D(40,40),0,Fade(valid ? GREEN : RED,0.6f));
            }
        }
        if (drawButtonInvisible(Vec2D(1375, 725),Vec2D(100, 100) , in.mousePos))
        {
            in.buttonSelected = 3;
        }
        if (drawButtonInvisible(Vec2D(710, 680),Vec2D(70, 70) , in.mousePos))
        {
            in.buttonSelected = 4;
        }
        if (drawButtonInvisible(Vec2D(465, 680),Vec2D(70, 70) , in.mousePos))
        {
            in.buttonSelected = 5;
        }
    }

}

void menuMain(DataHolder& in)
{
    in.buttonSelected = 0;
    
    if (drawButtonMenu(in, "Play", Vec2D(498, 345), Vec2D(455, 320),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Option",Vec2D(873, 345), Vec2D(860, 320),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Credit",Vec2D(475, 565), Vec2D(455, 540),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Exit",Vec2D(920, 565), Vec2D(860, 540),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    if (drawButtonInvisible(Vec2D(mod(1295-in.framecounter/3.0f,0,1920), 140),Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 5;
    }
    if (drawButtonInvisible(Vec2D(1500, 800), Vec2D(100, 100), in.mousePos))
    {
        in.buttonSelected = 6;
    }
}

void renderPlay(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Play", Vector2{660,0},100,4,BLACK);
    
    if (drawButtonMenu(in, "New", Vec2D(710,285), Vec2D(650, 240),Vec2D(250,140), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    if (drawButtonMenu(in, "Load", Vec2D(695,445), Vec2D(650, 400),Vec2D(250,140), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "Editor", Vec2D(665, 605), Vec2D(650, 580),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 4;
    }
}

void renderCredit(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTexturePro(in.textures.logoIsart, Rectangle{0,0,256,256},Rectangle{100, 350, 200,200},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.logo, Rectangle{0,0,300,300},Rectangle{1300, 350,200,200},Vector2{0,0}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Credit", Vector2{600,0},100,4,BLACK);
    DrawTextEx(in.fontTitle, "Quentin Lepine", Vector2{450,300},70,4,WHITE);
    DrawTextEx(in.fontTitle, "Antoine Mordant", Vector2{420,450},70,4,WHITE);
    DrawTextEx(in.fontTitle, "Umut Osmanoglu", Vector2{430,600},70,4,WHITE);
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
}

void renderOption(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Option", Vector2{600,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 300,500,100},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 400,500,100},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 500,500,100},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 600,500,160},Vector2{0,0}, 0, WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Master Volume: %.2f",in.masterVolume), Vector2{420,320},40,0,WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Effect Volume: %.2f",in.effectVolume), Vector2{420,420},40,0,WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Music Volume: %.2f",in.musicVolume), Vector2{420,520},40,0,WHITE);
    DrawTextEx(in.fontTitle, TextFormat("        Difficulty : \n%s", difficultyString[in.difficulty - 1]), Vector2{420,620},40,0,WHITE);
    if (drawButtonMenu(in, "+",Vec2D(955, 315), Vec2D(950, 315), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 315), Vec2D(1050, 315), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "+",Vec2D(955, 415), Vec2D(950, 415), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 415), Vec2D(1050, 415), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 5;
    }
    if (drawButtonMenu(in, "+",Vec2D(955, 515), Vec2D(950, 515), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 6;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 515), Vec2D(1050, 515), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 7;
    }
    if (drawButtonMenu(in, "+",Vec2D(955, 615), Vec2D(950, 615), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 8;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 615), Vec2D(1050, 615), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 9;
    }
    
}

void renderGameOption(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Option", Vector2{600,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 300,500,100},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 400,500,100},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.optionButton, Rectangle{0,0,540,160},Rectangle{400, 500,500,100},Vector2{0,0}, 0, WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Master Volume: %.2f",in.masterVolume), Vector2{420,320},40,0,WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Effect Volume: %.2f",in.effectVolume), Vector2{420,420},40,0,WHITE);
    DrawTextEx(in.fontTitle, TextFormat("Music Volume: %.2f",in.musicVolume), Vector2{420,520},40,0,WHITE);
    if (drawButtonMenu(in, "+",Vec2D(955, 315), Vec2D(950, 315), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 2;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 315), Vec2D(1050, 315), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 3;
    }
    if (drawButtonMenu(in, "+",Vec2D(955, 415), Vec2D(950, 415), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 4;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 415), Vec2D(1050, 415), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 5;
    }
    if (drawButtonMenu(in, "+",Vec2D(955, 515), Vec2D(950, 515), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 6;
    }
    if (drawButtonMenu(in, "-", Vec2D(1058, 515), Vec2D(1050, 515), Vec2D(50,50), in.mousePos))
    {
        in.buttonSelected = 7;
    }
}

void renderLoad(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Load", Vector2{650,0},100,4,BLACK);
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    for (int i = 0; i < 3; i++)
    {
        SaveData* tmp = &in.lists.renderDatas[i];
        if (tmp->timePlayed == 0) {
            DrawText("New File",950,305+i*160,20,BLACK);
        }
        else
        {
            DrawText(TextFormat("Time played : %.2d:%.2d",tmp->timePlayed/60, tmp->timePlayed%60),950,275+i*160,20,BLACK);
            if (tmp->maxLevel < 9) DrawText(TextFormat("Levels unlocked : %d",tmp->maxLevel+1),950,305+i*160,20,BLACK);
            else DrawText("All levels unlocked!",950,305+i*160,20,BLACK);
            if (in.lists.saveDatas.maxLevel == 10) DrawText(TextFormat("Max wave in HARDCORE : %d",tmp->maxWave),950,335+i*160,20,BLACK);
        }
        if (drawButtonMenu(in, TextFormat("File %d", i+1), Vec2D(690,285+i*160), Vec2D(650, 240+i*160),Vec2D(250,140), in.mousePos))
        {
            in.buttonSelected = i+2;
        }
    }
}

void renderSave(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Save to File", Vector2{650,0},100,4,BLACK);
    if (drawButtonMenu(in, "Continue", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if (drawButtonMenu(in, TextFormat("File %d", i+1), Vec2D(690,285+i*160), Vec2D(650, 240+i*160),Vec2D(250,140), in.mousePos))
        {
            in.buttonSelected = i+2;
        }
    }
}

void renderMenuMap(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Choose a map", Vector2{440,10},90,4,BLACK);
    for (int i = 0; i < 9; i++)
    {
        if (in.lists.saveDatas.maxLevel >= i && drawButtonMenu(in, TextFormat("Level %d", i+1), Vec2D(265+(i%3)*400,225+(i/3)*120), Vec2D(250+(i%3)*400, 200+(i/3)*120),Vec2D(280,100), in.mousePos))
        {
            in.buttonSelected = i+1;
        }
    }
    if (in.lists.saveDatas.maxLevel >= 9 && drawButtonMenu(in, "Level10", Vec2D(665, 585), Vec2D(650,560 ),Vec2D(280,100), in.mousePos))
    {
        in.buttonSelected = 10;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(280,100), in.mousePos))
    {
        in.buttonSelected = 11;
    }
    if (drawButtonMenu(in, "Custom", Vec2D(1060, 775), Vec2D(1050, 750),Vec2D(280,100), in.mousePos))
    {
        in.buttonSelected = 12;
    }
}

void renderMenuMapCustom(DataHolder& in)
{
    in.buttonSelected = 0;
    float width = in.screenWidth;
    float heigth = in.screenHeight;
    DrawTexturePro(in.textures.background, Rectangle{in.framecounter/3.0f,0,1600,1000},Rectangle{0,0,width,heigth},Vector2{0,0}, 0, WHITE);
    DrawTexturePro(in.textures.title, Rectangle{0,0,500,500},Rectangle{450, 0,1000,450},Vector2{150,150}, 0, WHITE);
    DrawTextEx(in.fontTitle, "Choose a map", Vector2{440,10},90,4,BLACK);
    for (int i = 0; i < 9; i++)
    {
        if (drawButtonMenu(in, TextFormat("Map %d", i+1), Vec2D(270+(i%3)*400,225+(i/3)*120), Vec2D(250+(i%3)*400, 200+(i/3)*120),Vec2D(280,100), in.mousePos))
        {
            in.buttonSelected = i+1;
        }
    }
    if (drawButtonMenu(in, "Map 10", Vec2D(670, 585), Vec2D(650,560 ),Vec2D(250,100), in.mousePos))
    {
        in.buttonSelected = 10;
    }
    if (drawButtonMenu(in, "Return", Vec2D(652, 785), Vec2D(640, 760),Vec2D(270,100), in.mousePos))
    {
        in.buttonSelected = 11;
    }
}