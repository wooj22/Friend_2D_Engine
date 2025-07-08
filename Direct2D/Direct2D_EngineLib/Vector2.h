#pragma once
#include <cmath>

class Vector2
{
public:
    float x;
    float y;

    // construct
    Vector2();
    Vector2(float x, float y);

    // operator overloading
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    // func
    float Magnitude() const;
    Vector2 Normalized() const;
};
