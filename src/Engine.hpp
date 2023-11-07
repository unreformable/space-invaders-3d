#pragma once

#include "SDL2/SDL.h"

#include <functional>
#include <string>



struct EngineProps
{
    int m_WindowWidth;
    int m_WindowHeight;
    std::string m_WindowTitle;
};

class Engine
{
public:
    using EventCallback = std::function<void(const SDL_Event&)>;

public:
    static void Initalize(const EngineProps& props);
    static void Terminate();

    static void LoopBegin();
    static void LoopEnd();

    static void RenderBegin();
    static void RenderEnd();

    static inline void SetEventCallback(EventCallback callback) { m_EventCallback = callback; }

    static inline float DeltaTime() { return m_DeltaTime; }

private:
    Engine(const Engine& other);
    Engine& operator=(const Engine& other);
    Engine(Engine&& other);
    Engine& operator=(Engine&& other);

private:
    static SDL_Window* m_Window;
    static SDL_GLContext m_Context;

    static float m_DeltaTime;
    static uint64_t m_LoopStartMs;

    static EventCallback m_EventCallback;
};