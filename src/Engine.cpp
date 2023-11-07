#include "Engine.hpp"

#include "Input.hpp"

#include "glad/glad.h"

#include <cassert>
#include <iostream>



SDL_Window* Engine::m_Window;
SDL_GLContext Engine::m_Context;

float Engine::m_DeltaTime;
uint64_t Engine::m_LoopStartMs;

Engine::EventCallback Engine::m_EventCallback;

void Engine::Initalize(const EngineProps& props)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initalize SDL2" << std::endl;
        assert(false);
    }
    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_Window = SDL_CreateWindow(
        props.m_WindowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        props.m_WindowWidth, props.m_WindowHeight,
        SDL_WINDOW_OPENGL
    );
    assert(m_Window != NULL);

    m_Context = SDL_GL_CreateContext(m_Window);
    assert(m_Context != NULL);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    
    // V-sync on
    SDL_GL_SetSwapInterval(1);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glViewport(0, 0, props.m_WindowWidth, props.m_WindowHeight);

    m_DeltaTime = 0.0f;
    m_LoopStartMs = SDL_GetPerformanceCounter();
}

void Engine::Terminate()
{
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Engine::LoopBegin()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        Input::Update(e);

        m_EventCallback(e);
    }
}

void Engine::LoopEnd()
{
    const GLenum error_code = glGetError();
    if(error_code != GL_NONE)
    {
        std::cerr << "OpenGL error. Error code: 0x" << std::hex << error_code << std::endl;
    }

    // DELTA TIME CALCULATION
    SDL_Delay(1);
    uint64_t loop_end_ms = SDL_GetPerformanceCounter();
    m_DeltaTime = static_cast<float>(loop_end_ms - m_LoopStartMs) / static_cast<float>(SDL_GetPerformanceFrequency());
    m_LoopStartMs = loop_end_ms;
}

void Engine::RenderBegin()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::RenderEnd()
{
    SDL_GL_SwapWindow(m_Window);
}