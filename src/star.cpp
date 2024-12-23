#include <SDL2/SDL.h>
#include <star.hpp>

Star::Star(string name, Vector2<> realPosition, double realRadius, double mass, int temperature)
{
    this->name = name;
    this->realPosition = realPosition;
    this->realRadius = realRadius;
    this->mass = mass;
    this->temperature = temperature;
}

int Star::GetTemperature() const
{
    return this->temperature;
}

void Star::SetTemperature(int temperature)
{
    this->temperature = temperature;
}