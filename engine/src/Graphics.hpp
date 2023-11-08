#pragma once

#include "Color.hpp"

#include "SDL2/SDL.h"

#include <string>



class Graphics
{
public:
    struct Config
    {
        uint32_t m_WindowWidth;
        uint32_t m_WindowHeight;
        std::string m_WindowTitle;
        Color m_ClearColor;
    };

public:
    static void Initalize(const Config& config);
    static void Terminate();

    static void Clear();
    static void Display();

    static void CheckForErrors();

    static void PinMouseToWindowCenter(bool pin_mouse);

private:
    Graphics(const Graphics& other);
    Graphics& operator=(const Graphics& other);
    Graphics(Graphics&& other);
    Graphics& operator=(Graphics&& other);

private:
    static SDL_Window* m_Window;
    static SDL_GLContext m_Context;
};