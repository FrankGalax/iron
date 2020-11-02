#include <math/vector.h>
#include <math.h>

ironBEGIN_NAMESPACE

Vector2f Vector2f::Zero(0.f, 0.f);

Vector2f::Vector2f() : m_X(0.f), m_Y(0.f)
{
}

Vector2f::Vector2f(float x, float y) : m_X(x), m_Y(y)
{
}

bool Vector2f::IsNull() const
{
    return fabs(m_X) <= ironTolerance && fabs(m_Y) <= ironTolerance;
}

float Vector2f::GetSquareLength() const
{
	return m_X * m_X + m_Y * m_Y;
}

Vector2f Vector2f::operator+(const Vector2f& other) const
{
	return Vector2f(m_X + other.m_X, m_Y + other.m_Y);
}

void Vector2f::operator+=(const Vector2f& other)
{
    m_X += other.m_X;
    m_Y += other.m_Y;
}

Vector2f Vector2f::operator-(const Vector2f& other) const
{
    return Vector2f(m_X - other.m_X, m_Y - other.m_Y);
}

Vector2f Vector2f::operator*(float operand) const
{
    return Vector2f(m_X * operand, m_Y * operand);
}

ironEND_NAMESPACE