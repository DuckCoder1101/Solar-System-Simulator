#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_image.h>

#include <planet.hpp>

Planet::Planet(
    string name,
    Vector2<> position,
    Vector2<> size,
    double mass,
    double translationVelocity,
    double orbitRadius,
    double orbitAngle,
    Star *star)
{
    this->name = name;
    this->position = position;
    this->size = size;
    this->mass = mass;
    this->translationVelocity = translationVelocity;
    this->orbitRadius = 0;
    this->orbitAngle = 0;
    this->star = star;
}

double Planet::GetTranslation() const
{
    return this->translationVelocity;
}

void Planet::SetTranslation(double translationVelocity)
{
    this->translationVelocity = translationVelocity;
}

double Planet::GetOrbitRadius() const
{
    return this->orbitRadius;
}

void Planet::SetOrbitRadius(double orbitRadius)
{
    this->orbitRadius = orbitRadius;
}

double Planet::GetOrbitAngle() const
{
    return this->orbitAngle;
}

void Planet::SetOrbitAngle(double orbitAngle)
{
    this->orbitAngle = orbitAngle;
}

Star* Planet::GetStar() const
{
    return this->star;
}

void Planet::DrawOrbit(SDL_Renderer *renderer, double scale, Vector2<int> screenSize)
{
    // // Draw orbit
    // SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);

    // for (int angle = 0; angle < 360; ++angle) {
    //     int x = screenPos.x + this->orbitRadius * cos(angle * M_PI / 180);
    //     int y = screenPos.y + this->orbitRadius * sin(angle * M_PI / 180);
    //     SDL_RenderDrawPoint(renderer, x, y);
    // }
}