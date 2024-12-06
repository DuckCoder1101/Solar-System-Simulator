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
    double translationVelocity;
    double orbitRadius;
    double orbitAngle;
    Star *star;

public:
    Planet(
        string name,
        Vector2<> position,
        Vector2<> size,
        double mass,
        double translationVelocity,
        double orbitRadius,
        double orbitAngle,
        Star *star);

    double GetTranslation() const;
    void SetTranslation(double translationVelocity);

    double GetOrbitRadius() const;
    void SetOrbitRadius(double orbitRadius);

    double GetOrbitAngle() const;
    void SetOrbitAngle(double orbitAngle);

    Star* GetStar() const;

    void DrawOrbit(SDL_Renderer *renderer, double scale, Vector2<int> screenSize);
};

#endif