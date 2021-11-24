#include "renderUtil.hpp"
#include "mathHelper.hpp"

Color getRGB(int frame)
{
    return ColorFromHSV(mod(frame*0.013f, 0.0f, 1.0f)*360.0f,0.5,1.0);
}