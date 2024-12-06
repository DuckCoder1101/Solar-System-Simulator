#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>
#include <SDL2/SDL.h>

template <typename T = double>
class Vector2
{
public:
    static const Vector2<T> zero;

    static T GetDistance(const Vector2<T> &a, const Vector2<T> &b);

    T x, y;

    Vector2(T x = 0, T y = 0);

    SDL_Point ToSDLPoint() const;
};

template <typename T>
const Vector2<T> Vector2<T>::zero = Vector2<T>(0, 0);

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
T Vector2<T>::GetDistance(const Vector2<T> &a, const Vector2<T> &b)
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
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
