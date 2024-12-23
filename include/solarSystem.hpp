#include <iostream>
#include <star.hpp>
#include <planet.hpp>
#include <vector2.hpp>
#include <rigidbody.hpp>
#include <SDL2/SDL.h>

class SolarSystem
{
    private:
        Star *sun = nullptr;
        vector<RigidBody *> celestialBodies;

        double radiusScale, positionScale;
        Vector2<int> screenSize;

    public:
        SolarSystem(Star *sun, vector<RigidBody*> planets, Vector2<int> screenSize);
        
        Star *GetSun() const;

        vector<RigidBody *> GetCelestialBodies() const;

        Vector2<int> GetScreenSize() const;
        void SetScreenSize(Vector2<int> screenSize);

        void addCelestialBody(RigidBody *celestialBody);

        void SetScale();

        void UpdateSystem(SDL_Renderer *renderer, double dt, Debug *debug);
};