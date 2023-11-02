#include "glad/glad.h"
#include "SDL2/SDL.h"

#include <cassert>
#include <iostream>


int main()
{
    const int window_w = 600;
    const int window_h = 800;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not initalize SDL2" << std::endl;
        return 1;
    }
    SDL_GL_LoadLibrary(NULL);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow("Space Invaders 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_OPENGL);
    assert(window != NULL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    assert(context != NULL);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    
    // V-sync on
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glViewport(0, 0, window_w, window_h);

    bool running = true;
    while(running == true)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}