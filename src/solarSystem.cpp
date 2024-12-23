#include <solarSystem.hpp>
#include <vector2.hpp>
#include <SDL2/SDL.h>

SolarSystem::SolarSystem(Star *sun, vector<RigidBody *> planets, Vector2<int> screenSize)
{
    this->celestialBodies = planets;
    this->screenSize = screenSize;
    this->sun = sun;

    this->celestialBodies.push_back(this->sun);
    this->SetScale();
}

Star *SolarSystem::GetSun() const
{
    return this->sun;
}

vector<RigidBody *> SolarSystem::GetCelestialBodies() const
{
    return this->celestialBodies;
}

void SolarSystem::addCelestialBody(RigidBody *celestialBody)
{
    this->celestialBodies.push_back(celestialBody);
    this->SetScale();
}

Vector2<int> SolarSystem::GetScreenSize() const
{
    return this->screenSize;
}

void SolarSystem::SetScreenSize(Vector2<int> screenSize)
{
    this->screenSize = screenSize;
}

void SolarSystem::SetScale()
{
    double maxRealRadius = 0;
    double maxRealDistance = 0;
    Vector2 maxPosition;

    for (const auto body : this->celestialBodies)
    {
        if (body->GetRealRadius() > maxRealRadius)
        {
            maxRealRadius = body->GetRealRadius();
        }

        double distance = Vector2<>::GetDistance(
            this->sun->GetRealPosition(), 
            body->GetRealPosition());

        cout << distance;

        if (distance > maxRealDistance)
        {
            maxRealDistance = distance;
        }
    }

    if (maxRealDistance == 0 || maxRealRadius == 0)
    {
        cerr << "Error: maxRealDistance or maxRealRadius is 0" << endl;
        exit(-1);
        return;
    }

    double sX = double(this->screenSize.x / 2);
    double sY = double(this->screenSize.y / 2);

    this->radiusScale = sX * 0.4 / maxRealRadius;
    this->positionScale = sY * 0.9 / maxRealDistance;
}

void SolarSystem::UpdateSystem(SDL_Renderer *renderer, double dt, Debug *debug)
{
    for (RigidBody *body : celestialBodies)
    {
        for (RigidBody *otherBody : celestialBodies)
        {
            if (body != otherBody)
            {
                RigidBody::CalcGravityAttraction(body, otherBody);
            }
        }

        body->UpdateBody(dt, debug);

        body->Scale(this->radiusScale, this->positionScale);
        body->DrawGameObject(renderer, screenSize);
    }
}