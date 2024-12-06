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

    Vector2<double> position;
    Vector2<double> size;
    double rotation = 0;

    SDL_Texture *texture;
    Vector2<int> textureSize;

    bool visible = true;
    bool active = true;

public:
    static constexpr float scale = 1.0f;

    GameObject(string name = "gameObject", Vector2<> position = Vector2(), Vector2<> size = Vector2());

    string GetName() const;
    void SetName(string name);

    Vector2<> GetPosition() const;
    void SetPosition(Vector2<> position);

    Vector2<> GetSize() const;
    void SetSize(Vector2<> size);

    double GetRotation() const;
    void SetRotation(double rotation);

    Vector2<int> GetTextureSize() const;
    void SetTextureSize(Vector2<int> textureSize);

    bool GetVisible() const;
    void SetVisible(bool visible);

    bool GetActive() const;
    void SetActive(bool active);

    void LoadTexture(SDL_Renderer *renderer, const u_char *bytes, u_int length);

    void DrawGameObject(SDL_Renderer *renderer, Vector2<int> screenSize);
};

#endif