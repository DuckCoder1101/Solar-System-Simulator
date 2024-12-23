#include <gameObject.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

GameObject::GameObject(string name, Vector2<int> position, double radius)
{
    this->name = name;
    this->position = position;
    this->radius = radius;
}

string GameObject::GetName() const
{
    return this->name;
}

void GameObject::SetName(string name)
{
    this->name = name;
}

Vector2<int> GameObject::GetPosition() const
{
    return this->position;
}

void GameObject::SetPosition(Vector2<int> position)
{
    this->position = position;
}

double GameObject::GetRadius() const
{
    return this->radius;
}

void GameObject::SetRadius(double radius)
{
    this->radius = radius;
}

bool GameObject::GetVisible() const
{
    return this->visible;
}

void GameObject::SetVisible(bool visible)
{
    this->visible = visible;
}

void GameObject::LoadTexture(SDL_Renderer *renderer, const u_char *bytes, u_int length)
{
    SDL_RWops *rw = SDL_RWFromMem(const_cast<u_char *>(bytes), length);
    if (!rw)
    {
        cerr << "Failed to create RWops from memory: " << this->name << " " << SDL_GetError() << endl;
        return;
    }

    SDL_Texture *texture = IMG_LoadTexture_RW(renderer, rw, 1);
    if (!texture)
    {
        cerr << "Could not load texture: " << this->name << " " << SDL_GetError() << endl;
        return;
    }

    this->texture = texture;
}

void GameObject::DrawGameObject(SDL_Renderer *renderer, Vector2<int> screenSize)
{
    Vector2<int> center = Vector2<int>(
        this->position.x - this->radius,
        this->position.y - this->radius);

    int size = round(this->radius * 2);

    if (this->active && this->visible)
    {
        SDL_Rect rect = {
            center.x,
            center.y,
            size,
            size};

        SDL_RenderCopy(renderer, this->texture, NULL, &rect);
    }
}