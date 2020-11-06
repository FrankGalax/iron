#pragma once

#include <iron.h>

ironBEGIN_NAMESPACE

class Vector2f
{
public:
    static Vector2f Right;
    static Vector2f Down;
    static Vector2f Left;
    static Vector2f Up;
    static Vector2f Zero;

    Vector2f();
    Vector2f(float x, float y);

    void SetX(float x) { m_X = x; }
    float GetX() const { return m_X; }
    void SetY(float y) { m_Y = y; }
    float GetY() const { return m_Y; }
    
    bool IsNull() const;
    bool Equals(const Vector2f& other) const;
	float GetSquareLength() const;

	Vector2f operator+(const Vector2f& other) const;
    void operator+=(const Vector2f& other);
    Vector2f operator-(const Vector2f& other) const;
    Vector2f operator*(float operand) const;
private:
    float m_X = 0.f;
    float m_Y = 0.f;
};

ironEND_NAMESPACE