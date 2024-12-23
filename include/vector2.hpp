#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <SDL2/SDL.h>
#include <string>

using std::pow;
using std::sqrt;
using std::string;
using std::to_string;

template <typename T = double>
class Vector2
{
public:
    static const Vector2<T> zero;

    static double GetDistance(const Vector2<T> &a, const Vector2<T> &b);

    T x, y;

    Vector2(T x = 0, T y = 0);

    double GetMagnitude() const;
    Vector2<> Normalize() const;
     
    string ToString() const;
    SDL_Point ToSDLPoint() const;
};

template <typename T>
const Vector2<T> Vector2<T>::zero = Vector2<T>(0, 0);

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

// Operators

template <typename T>
bool operator==(const Vector2<T> &a, const Vector2<T> &b)
{
    return a.x == b.x && a.y == b.y;
}

template <typename T>
bool operator!=(const Vector2<T> &a, const Vector2<T> &b)
{
    return a.x != b.x || a.y != b.y;
}

template <typename T>
Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
{
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

template <typename T>
Vector2<T> operator+=(Vector2<T> &a, const Vector2<T> &b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename T>
Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
{
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

template <typename T>
Vector2<T> operator-=(Vector2<T> &a, const Vector2<T> &b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template <typename T>
Vector2<T> operator*(Vector2<T> a, double scalar)
{
    return Vector2<T>(a.x * scalar, a.y * scalar);
}

template <typename T>
Vector2<T> operator/(Vector2<T> a, double scalar)
{
    return Vector2<T>(a.x * scalar, a.y * scalar);
}

// Methods

template <typename T>
double Vector2<T>::GetMagnitude() const
{
    return sqrt(x * x + y * y);
}

template <typename T>
Vector2<> Vector2<T>::Normalize() const
{
    double magnitude = this->GetMagnitude();

    if (magnitude == 0)
    {
        return Vector2<>::zero;
    }

    return Vector2<>(this->x / magnitude, this->y / magnitude);
}

template <typename T>
double Vector2<T>::GetDistance(const Vector2<T> &a, const Vector2<T> &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

template <typename T>
string Vector2<T>::ToString() const
{
    return "(" + to_string(this->x) + ", " + to_string(this->y) + ")";
}

template <typename T>
SDL_Point Vector2<T>::ToSDLPoint() const
{
    SDL_Point point;
    point.x = static_cast<int>(this->x);
    point.y = static_cast<int>(this->y);
    return point;
}

#endif
