#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

#include <planet.hpp>
#include <star.hpp>
#include <vector2.hpp>
#include <textures.hpp>
#include <solarSystem.hpp>
#include <debug.hpp>

// C++ com janelas graficas - Sistema Solar

using std::cerr;
using std::endl;
using std::function;
using std::string;
using std::unordered_map;
using std::vector;

bool isWindowFocused = false;
bool isRunning = false;

Vector2<int> screenSize;
Vector2<int> screenCenter;

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_DisplayMode displayMode;

// Debug window
Debug *debug = nullptr;

// Delta time
Uint32 lastTime = 0;
double deltaTime = 0;

SolarSystem *solarSystem = nullptr;

unordered_map<SDL_Keycode, function<void()>> keyMapping = {
    {
        SDLK_ESCAPE,
        []() {
            isRunning = false;
        }
    }
};

void Loop()
{
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        else if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (keyMapping.find(key) != keyMapping.end())
            {
                keyMapping[key]();
            }
        }

        else if (event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            isWindowFocused = true;
        }

        else if (event.type == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            isWindowFocused = false;
        }
    }
    SDL_RenderClear(renderer);

    solarSystem->UpdateSystem(renderer, deltaTime, debug);

    // Update main window
    SDL_RenderPresent(renderer);

    // Update debug window
    debug->Loop();
}

int main()
{
    // Video initializing error
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return -1;
    }

    // Image initializing error
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        cerr << "IMG_Init Error: " << IMG_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    // Get display mode
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    {
        cout << "Couldn't get display mode: " << SDL_GetError() << endl;
        return 1;
    }

    // Window
    window = SDL_CreateWindow(
        "Solar System Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        displayMode.w,
        displayMode.h,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        cerr << "Couldn't create window: " << SDL_GetError() << endl;

        SDL_Quit();
        return -1;
    }

    // Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        cerr << "Couldn't create renderer: " << SDL_GetError() << endl;

        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Full screen
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Window size
    screenSize = Vector2<int>(displayMode.w, displayMode.h);
    screenCenter = Vector2<int>(screenSize.x / 2, screenSize.y / 2);

    // Active log and debug window
    debug = new Debug("./log.txt");
    debug->StartGraphics(screenSize);

    // Sun
    Star *sun = new Star(
        "Sol",
        Vector2<>(0, 0),
        696340,
        1.989 * 10e30,
        5772);
    sun->LoadTexture(renderer, __assets_sun_png, __assets_sun_png_len);

    // Planets
    vector<RigidBody *> planets;

    planets.push_back(
        new Planet(
            "Earth",
            Vector2<>(1.496 * 10e11, 0),
            6371,
            5.972 * 10e24,
            Vector2<>(0, 0),
            sun));
    planets[0]->LoadTexture(renderer, __assets_earth_png, __assets_earth_png_len);

    // Solar system
    solarSystem = new SolarSystem(
        sun,
        planets,
        Vector2<int>(screenSize.x, screenSize.y));

    // Debug
    debug->AddDataType("Earth velocity", {255, 0, 0});
    debug->AddDataType("Sun velocity", {0, 0, 255});

    isRunning = true;

    while (isRunning)
    {
        Loop();
    }

    debug->StopGraphics();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}