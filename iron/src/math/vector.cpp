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

Vector2f Vector2f::operator-(const Vector2f& other) const
{
    return Vector2f(m_X - other.m_X, m_Y - other.m_Y);
}

ironEND_NAMESPACE