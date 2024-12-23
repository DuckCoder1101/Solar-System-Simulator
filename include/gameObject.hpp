#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include <vector2.hpp>

using std::string;
using std::vector;

class GameObject
{
protected:
    string name;

    Vector2<int> position;
    double radius;

    SDL_Texture *texture;

    bool visible = true;
    bool active = true;

public:
    static constexpr float scale = 1.0f;

    GameObject(string name = "gameObject", Vector2<int> position = Vector2<int>(), double radius = 0.0f);

    string GetName() const;
    void SetName(string name);

    Vector2<int> GetPosition() const;
    void SetPosition(Vector2<int> position);

    double GetRadius() const;
    void SetRadius(double radius);

    bool GetVisible() const;
    void SetVisible(bool visible);

    bool GetActive() const;
    void SetActive(bool active);

    void LoadTexture(SDL_Renderer *renderer, const u_char *bytes, u_int length);

    void DrawGameObject(SDL_Renderer *renderer, Vector2<int> screenSize);
};

#endif