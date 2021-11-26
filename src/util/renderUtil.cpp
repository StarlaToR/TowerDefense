#include "renderUtil.hpp"

Color getRGB(size_t frame)
{
    return ColorFromHSV(mod(frame*0.013f, 0.0f, 1.0f)*360.0f,0.5,1.0);
}

float getFade(size_t frame) {
    size_t tmp = frame%120;
    if (tmp >= 60)
    {
        return (120-tmp)/60.0f;
    }
    return tmp/60.0f;
}

Rectangle toRayLibRectangle(Vec2D origin, Vec2D rectSize)
{
    return (Rectangle){origin.x, origin.y, rectSize.x, rectSize.y};
}

void DrawTileMap(DataHolder* in, RenderType type)
{
    for (int i = 0; i < in->map.getWidth()*in->map.getHeight(); i++)
    {
        Vec2D tilePos = Vec2D(i%in->map.getWidth(),i/in->map.getWidth());
        Vec2D origin = Vec2D(50,50)+Vec2D(48,48)*tilePos;
        char tile = in->map.getTileAt(tilePos);
        DrawTexturePro(in->tileTexture,in->tiles.tileCrops.at(tile),toRayLibRectangle(origin,Vec2D(48,48)),{0,0},0.0f,WHITE);
        if (type >= EXTENDED)
        {
            if (tile >= ROAD_THREEWAY_FORCE_NORTH && tile <= ROAD_THREEWAY_FORCE_WEST)
            {
                Vec2D center = origin + Vec2D(24,24);
                switch (tile)
                {
                case ROAD_THREEWAY_FORCE_NORTH:
                    DrawTriangle(center+Vec2D(-10,4),center+Vec2D(10,4),center+Vec2D(0,-6),Fade(RED,0.4));
                    break;

                case ROAD_THREEWAY_FORCE_EAST:
                    DrawTriangle(center+Vec2D(-4,-10),center+Vec2D(-4,10),center+Vec2D(6,0),Fade(RED,0.4));
                    break;
                
                case ROAD_THREEWAY_FORCE_SOUTH:
                    DrawTriangle(center+Vec2D(10, -4),center+Vec2D(-10,-4),center+Vec2D(0,6),Fade(RED,0.4));
                    break;

                case ROAD_THREEWAY_FORCE_WEST:
                    DrawTriangle(center+Vec2D(4,10),center+Vec2D(4,-10),center+Vec2D(-6,0),Fade(RED,0.4));
                    break;

                default:
                    break;
                }
            }
        }
        if (type >= BORDER)
        {
            DrawRectangleLinesEx(toRayLibRectangle(origin,Vec2D(48,48)),1,BLACK);
        }
        if (type  == DEBUG)
        {
            DrawText(TextFormat("%d",in->map.getTileAt(tilePos)),origin.x+2,origin.y+2,10,BLACK);
        }
    }
}