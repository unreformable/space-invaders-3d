#include "Graphics.hpp"

#include "glad/glad.h"

#include <cassert>
#include <iostream>



SDL_Window* Graphics::m_Window{};
SDL_GLContext Graphics::m_Context{};

void Graphics::Initalize(const Config& config)
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
        config.m_WindowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        config.m_WindowWidth, config.m_WindowHeight,
        SDL_WINDOW_OPENGL
    );
    assert(m_Window != NULL);

    m_Context = SDL_GL_CreateContext(m_Window);
    assert(m_Context != NULL);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    
    // V-sync on
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glViewport(0, 0, config.m_WindowWidth, config.m_WindowHeight);

    glClearColor(config.m_ClearColor.r, config.m_ClearColor.g, config.m_ClearColor.b, config.m_ClearColor.a);
}

void Graphics::Terminate()
{
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Graphics::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::Display()
{
    SDL_GL_SwapWindow(m_Window);
}

void Graphics::CheckForErrors()
{
    const GLenum error_code = glGetError();
    if(error_code != GL_NONE)
    {
        std::cerr << "OpenGL error. Error code: 0x" << std::hex << error_code << std::endl;
    }
}

void Graphics::PinMouseToWindowCenter(bool pin_mouse)
{
    pin_mouse == true ? SDL_SetRelativeMouseMode(SDL_TRUE) : SDL_SetRelativeMouseMode(SDL_FALSE);
}