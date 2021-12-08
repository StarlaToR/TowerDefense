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

    Vec2D Vec2D::applyRotation(RotationMatrix matrix)
    {
        float res[2] = {0};
        float input[2] = {x, y};
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                res[j] += input[i]*matrix.content[j][i];
            }
        }
        return Vec2D(res[0], res[1]);
    }

    bool Vec2D::isIntEquivalent(Vec2D a)
    {
        int x1 = (int)x;
        int y1 = (int)y;
        int x2 = (int)a.x;
        int y2 = (int)a.y;
        return (x1 == x2 && y1 == y2);
    }

    RotationMatrix::RotationMatrix(float angle)
    {
        float tmpCos = cosf(toRadians(angle));
        float tmpSin = sinf(toRadians(angle));
        content[0][0] = tmpCos;
        content[0][1] = -tmpSin;
        content[1][0] = tmpSin;
        content[1][1] = tmpCos;
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