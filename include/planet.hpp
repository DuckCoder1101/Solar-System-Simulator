#ifndef PLANET_H
#define PLANET_H

#include <SDL2/SDL.h>
#include <vector2.hpp>
#include <rigidbody.hpp>
#include <star.hpp>

using namespace std;

class Planet : public RigidBody
{
private:
    Star *star;

public:
    Planet(
        string name,
        Vector2<> realPosition,
        double realRadius,
        double mass,
        Vector2<> v0,
        Star *star);

    Star *GetStar() const;

    void DrawOrbit(SDL_Renderer *renderer, double scale, Vector2<int> screenSize);
};

#endif