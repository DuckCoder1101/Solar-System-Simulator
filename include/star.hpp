#ifndef STAR_H
#define STAR_H

#include <SDL2/SDL.h>
#include <vector2.hpp>
#include <rigidbody.hpp>

class Star : public RigidBody {
private:
    int temperature;

public:
    Star(string name = "star", Vector2<> position = Vector2(), Vector2<> size = Vector2(), int temperature = 1000);

    int GetTemperature() const;
    void SetTemperature(int temperature);

    void DrawStar(SDL_Renderer *renderer);
};

#endif