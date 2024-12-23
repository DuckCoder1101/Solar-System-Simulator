#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>

#include <debug.hpp>

using std::cerr;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::minmax_element;
using std::numeric_limits;
using std::string;

const int Debug::UPDATES_IN_SCREEN = 10;
const Uint32 Debug::UPDATE_DELAY = 1000;

Debug::Debug(string logPath)
{
    this->logPath = logPath;

    bool existsLogFile = std::filesystem::exists(logPath);

    if (!existsLogFile)
    {
        std::ofstream logFile(logPath);

        if (!logFile.is_open())
        {
            cerr << "Error: Failed to create log file" << endl;
            return;
        }

        logFile.close();
    }
}

void Debug::StartGraphics(Vector2<int> screenSize)
{
    this->screenSize = screenSize;
    this->window = SDL_CreateWindow(
        "Graphics Debug",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenSize.x,
        screenSize.y,
        SDL_WINDOW_SHOWN);

    if (!this->window)
    {
        cerr << "Error: Failed to create debug window" << endl;
        return;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if (!this->renderer)
    {
        cerr << "Error: Failed to create debug renderer" << endl;

        SDL_DestroyWindow(this->window);
        return;
    }

    this->isGraphicsActive = true;
}

void Debug::Loop()
{
    if (!isGraphicsActive)
        return;

    // Window events
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE))
        {
            this->StopGraphics();
        }

        else if (event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
        {
            this->isGraphicsFocused = true;
        }

        else if (event.type == SDL_WINDOWEVENT_FOCUS_LOST)
        {
            this->isGraphicsFocused = false;
        }
    }

    SDL_RenderClear(this->renderer);

    double maxValue = numeric_limits<double>::min();
    double minValue = numeric_limits<double>::max();

    double minTime = numeric_limits<int>::max();
    double maxTime = numeric_limits<int>::min();

    for (auto &pair : this->data)
    {
        pair.second.points.erase(pair.second.points.begin());

        auto data = pair.second.points;

        if (!data.empty())
        {
            auto [localMinValue, localMaxValue] = minmax_element(data.begin(), data.end(), [](Point &a, Point &b)
                                                                 { return a.value < b.value; });

            auto [localMinTime, localMaxTime] = minmax_element(data.begin(), data.end(), [](Point &a, Point &b)
                                                               { return a.time < b.time; });

            maxValue = max(maxValue, localMaxValue->value);
            minValue = min(minValue, localMinValue->value);

            maxTime = max(maxTime, localMaxTime->time);
            minTime = min(minTime, localMinTime->time);
        }
    }

    for (auto &pair : this->data)
    {
        DebugData data = pair.second;
        SDL_SetRenderDrawColor(
            this->renderer,
            data.color.r, data.color.g, data.color.b,
            data.color.a);

        for (auto &point : pair.second.points)
        {
            double value = point.value;
            double time = point.time;

            int y = round((value - minValue) / (maxValue - minValue) * this->screenSize.y);
            int x = round((time - minTime) / (maxTime - minTime) * this->screenSize.x);

            // if (data.data.size() == 1)
            // {
            SDL_RenderDrawPoint(this->renderer, x, y);
            // }

            // else if (i > 0)
            // {
            //     SDL_RenderDrawLine(
            //         this->renderer,
            //         i -1 * scaleX,
            //         data.data[i] * scaleY,
            //         i * scaleX,
            //         data.data[i + 1] * scaleY);
            // }
        }
    }

    SDL_RenderPresent(this->renderer);
}

void Debug::StopGraphics()
{
    this->isGraphicsActive = false;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Debug::AddDataType(string key, SDL_Color color)
{
    this->data[key] = {
        color : color,
        points : vector<Point>()
    };
}

void Debug::AddDataPoints(string key, vector<Point> points)
{
    this->data[key].points.insert(this->data[key].points.end(), points.begin(), points.end());
}

bool Debug::GetIsWindowFocused() const
{
    return this->isGraphicsFocused;
}