#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_image.h>

#include <planet.hpp>

Planet::Planet(
    string name,
    Vector2<> realPosition,
    double realRadius,
    double mass,
    Vector2<> v0,
    Star *star)
{
    this->name = name;
    this->realPosition = realPosition;
    this->realRadius = realRadius;
    this->mass = mass;
    this->velocity = v0;
    this->star = star;
}

Star *Planet::GetStar() const
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