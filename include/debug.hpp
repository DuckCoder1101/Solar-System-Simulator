#ifndef DEBUG_H
#define DEBUG_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <vector2.hpp>

using std::string;
using std::unordered_map;
using std::vector;

struct DebugData
{
    SDL_Color color;
    vector<Point> points;
};

struct Point
{
    double value;
    double time;
};

class Debug
{
private:
    static const Uint32 UPDATE_DELAY;
    static const int UPDATES_IN_SCREEN;

    unordered_map<string, DebugData> data;
    string logPath = "";

    bool isGraphicsActive = false;
    bool isGraphicsFocused = true;

    Uint32 frameStart;
    Vector2<int> screenSize;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Debug(string logPath);

    void StartGraphics(Vector2<int> screenSize);
    void Loop();
    void StopGraphics();

    void AddDataType(string key, SDL_Color color);
    void AddDataPoints(string key, vector<Point> points);

    void Log(const string msg);

    bool GetIsWindowFocused() const;
};

#endif