#include <gameObject.hpp>
#include <SDL2/SDL_image.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

GameObject::GameObject(string name, Vector2<> position, Vector2<> size)
{
    this->name = name;
    this->position = position;
    this->size = size;
}

string GameObject::GetName() const
{
    return this->name;
}

void GameObject::SetName(string name)
{
    this->name = name;
}

Vector2<> GameObject::GetPosition() const
{
    return this->position;
}

void GameObject::SetPosition(Vector2<> position)
{
    this->position = position;
}

Vector2<> GameObject::GetSize() const
{
    return this->size;
}

void GameObject::SetSize(Vector2<> size)
{
    this->size = size;
}

double GameObject::GetRotation() const
{
    return this->rotation;
}

void GameObject::SetRotation(double rotation)
{
    this->rotation = rotation;
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
    SDL_RWops* rw = SDL_RWFromMem(const_cast<u_char*>(bytes), length);
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
    int textureWidth, textureHeight;

    if (SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight))
    {
        this->textureSize = Vector2(1, 1);
        cerr << "Could not load texture size for gameObject " << this->name << SDL_GetError() << endl;
    }

    else
    {
        cout << "Texture size for gameObject " << this->name << ": " << textureWidth << ", " << textureHeight << endl;
        this->textureSize = Vector2(textureWidth, textureHeight);
    }
}

void GameObject::DrawGameObject(SDL_Renderer *renderer, Vector2<int> screenSize)
{
    Vector2 screenPos = Vector2(
        static_cast<int>((this->position.x / this->scale) + (screenSize.x / 2)),
        static_cast<int>((this->position.y / this->scale) + (screenSize.y / 2)));

    cout << "GameObject: " << this->name << " position: " << screenPos.x << ", " << screenPos.y << endl;

    // Draw planet
    SDL_Rect rect = {
        screenPos.x - this->textureSize.x / 2,
        screenPos.y - this->textureSize.y / 2,
        static_cast<int>(this->textureSize.x),
        static_cast<int>(this->textureSize.y)};

    SDL_RenderCopy(renderer, this->texture, NULL, &rect);
}