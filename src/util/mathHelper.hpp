#pragma once

#include <math.h>
#include <stdbool.h>

#define VEC2D_COLLINEAR_PRECISION 0.001f
#define VEC2D_HIGH_VALUE 1e20f

class Vec2D {
    public:
        float x;
        float y;

        // Return a new empty Vec2D
        Vec2D() : x(0), y(0) {}
    
        // Return a new Vec2D initialised with 'a' and 'b'
        Vec2D(float a, float b) : x(a), y(b) {}
    
        // Return a new Vec2D initialised with 'in'
        Vec2D(const Vec2D& in) : x(in.x), y(in.y) {}
    
        // Return the length squared of 'in'
        float lengthSquared();
    
        // Return the lenght of the given Vector
        float getLength();
    
        // Return a new vector wich is the sum of 'a' and 'b'
        Vec2D operator+ (const Vec2D& a);
    
        // Return a new vector wich is the substraction of 'a' and 'b'
        Vec2D operator- (const Vec2D& a);
    
        // Return the result of the aritmetic multiplication of 'a' and 'b'
        Vec2D operator* (const Vec2D& a);
    
        // Return the result of the aritmetic multiplication of 'a' and 'b'
        Vec2D operator* (const float& a);
    
        // Return the result of the aritmetic division of 'a' and 'b', will return 'a' * VEC2D_HIGH_VALUE if 'b' is equal 0;
        Vec2D operator/ (const float& b);
    
        // Return tue if 'a' and 'b' are collinears (Precision defined by VEC2D_COLLINEAR_PRECISION)
        bool isCollinearWith(Vec2D a);
    
        // Return the dot product of 'a' and 'b'
        float dotProduct(Vec2D a);
    
        // Return the z component of the cross product of 'a' and 'b'
        float crossProduct(Vec2D a);
    
        // Return a vector with the same direction that 'in', but with length 1
        Vec2D unitVector();
    
        // Return a vector of length 'in' and with an opposite direction
        Vec2D negate();
    
        // Return the normal vector of 'in'
        Vec2D getNormal();

        // return true if 'a' converted to int is equivalent to 'in' converted to int
        bool isIntEquivalent(Vec2D a);

        #ifdef VEC2_TO_RAYLIB_VECTOR2
            VEC2_TO_RAYLIB_VECTOR2
        #endif
};

// Return the given angular value in degres converted to radians
float toRadians(float in);

float cut(float in, float min, float max);

float mod(float in, float min, float max);
