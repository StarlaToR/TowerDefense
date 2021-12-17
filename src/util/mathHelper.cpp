#include "mathHelper.hpp"


    float Vec2D::lengthSquared()
    {
        return (x * x + y * y);
    }

    float Vec2D::getLength()
    {
        return sqrtf(lengthSquared());
    }

    Vec2D Vec2D::operator+ (const Vec2D& a)
    {
        Vec2D res = Vec2D(a.x + this->x, a.y + this->y);
        return res;
    }

    Vec2D Vec2D::operator- (const Vec2D& a)
    {
        Vec2D res = Vec2D(this->x - a.x, this->y - a.y);
        return res;
    }

    Vec2D Vec2D::operator* (const Vec2D& a)
    {
        Vec2D res = Vec2D(this->x * a.x, this->y * a.y);
        return res;
    }

    Vec2D Vec2D::operator* (const float& a)
    {
        Vec2D res = Vec2D(this->x * a, this->y * a);
        return res;
    }

    Vec2D Vec2D::operator/ (const float& a)
    {
        if (a == 0.0) return operator*(VEC2D_HIGH_VALUE);
        Vec2D res = operator*(1/a);
        return res;
    }

    bool Vec2D::isCollinearWith(Vec2D a)
    {
        float res = a.x * y - a.y * x;
        return (res < VEC2D_COLLINEAR_PRECISION);
    }

    float Vec2D::dotProduct(Vec2D a)
    {
        return (a.x * x + a.y * y);
    }

    float Vec2D::crossProduct(Vec2D a)
    {
        return (x * a.y - y* a.x);
    }

    Vec2D Vec2D::unitVector()
    {
        return operator/(getLength());
    }

    Vec2D Vec2D::negate()
    {
        return operator*(-1);
    }

    Vec2D Vec2D::getNormal()
    {
        return Vec2D(-y, x);
    }

    bool Vec2D::isIntEquivalent(Vec2D a)
    {
        int x1 = (int)(x>=0?x:x-1);
        int y1 = (int)(y>=0?y:y-1);
        int x2 = (int)a.x;
        int y2 = (int)a.y;
        return (x1 == x2 && y1 == y2);
    }

    float toRadians(float in)
    {
        return in/180.0*M_PI;
    }

    float cut(float in, float min, float max)
    {
        if (in < min) in = min;
        if (in > max) in = max;
        return in;
    }

    float mod(float in, float min, float max)
    {
        while(in < min) in += max-min;
        while (in > max) in -= max-min;
        return in;
    }