#pragma once

#include "SDL2/SDL.h"

#include <string>



struct EngineProps
{
    int m_WindowWidth;
    int m_WindowHeight;
    std::string m_WindowTitle;
};

// Please, do not create two objects of this class (this note > singleton)
class Engine
{
public:
    Engine(const EngineProps& props);
    ~Engine();

    void LoopBegin();
    void LoopEnd();

    void RenderBegin();
    void RenderEnd();

    inline float DeltaTime() const { return m_DeltaTime; }

private:
    Engine(const Engine& other);
    Engine& operator=(const Engine& other);
    Engine(Engine&& other);
    Engine& operator=(Engine&& other);

private:
    SDL_Window* m_Window;
    SDL_GLContext m_Context;

    float m_DeltaTime;
    uint64_t m_LoopStartMs;
};