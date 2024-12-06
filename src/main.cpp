#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>
#include <vector>

#include <planet.hpp>
#include <star.hpp>
#include <vector2.hpp>
#include <textures.hpp>

// C++ com janelas graficas - Sistema Solar

using std::cerr;
using std::endl;
using std::string;
using std::vector;

// Consts janela
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const Vector2 SCREEN_SIZE = Vector2(SCREEN_WIDTH, SCREEN_HEIGHT);

const int FRAME_RATE = 60;
const int DT = 6;

bool isRunning = false;
SDL_Event event;
SDL_Renderer *renderer;

// Game objects
Star star;
vector<Planet> planets;

void loop()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }

    SDL_RenderClear(renderer);
    star.DrawGameObject(renderer, SCREEN_SIZE);

    for (Planet &planet : planets)
    {
        planet.UpdateBody(DT);
        planet.DrawGameObject(renderer, SCREEN_SIZE);
    }

    SDL_RenderPresent(renderer);
}

int main()
{
    // Video initializing error
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erro ao inicializar SDL2: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Image initializing error
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Janela
    SDL_Window *window = SDL_CreateWindow(
        "Solar System Simulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;

        SDL_Quit();
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cerr << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    star = Star("Sol", Vector2<>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2<>(50, 50), 1000);
    star.LoadTexture(renderer, __assets_sun_png, __assets_sun_png_len);

    // planets.push_back(Planet("Terra", Vector2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4), Vector2(1,1), 1, 1, 10, 0, &star));
    // planets[0].LoadTexture(renderer, __assets_earth_png, __assets_earth_png_len);

    isRunning = true;
    while (isRunning)
    {
        loop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}