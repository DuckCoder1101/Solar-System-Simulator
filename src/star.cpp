#include <SDL2/SDL.h>
#include <star.hpp>

Star::Star(string name, Vector2<> position, Vector2<> size, int temperature) {
    this->name = name;
    this->position = position;
    this->size = size;
    this->temperature = temperature;
}

int Star::GetTemperature() const {
    return this->temperature;
}

void Star::SetTemperature(int temperature) {
    this->temperature = temperature;
}