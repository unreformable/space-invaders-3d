#include "Bitmap3D.hpp"
#include "Camera.hpp"
#include "CoordinateSystem.hpp"
#include "Invaders.hpp"
#include "LaserCannon.hpp"
#include "Program.hpp"
#include "Utils.hpp"

#include "glad/glad.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "SDL2/SDL.h"

#include <cassert>
#include <iostream>



int main()
{
    // SETUP
    const int window_w = 1280;
    const int window_h = 720;

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

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow("Space Invaders 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_OPENGL);
    assert(window != NULL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    assert(context != NULL);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    
    // V-sync on
    SDL_GL_SetSwapInterval(1);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glViewport(0, 0, window_w, window_h);

    Program program;
    program.Load("../assets/shaders/model.vs", "../assets/shaders/model.fs");

    // GAME OBJECTS
    Invaders invaders;

    LaserCannon cannon;
    cannon.SetPosition({0, 0, 50});

    // CAMERA
    const glm::mat4 proj = glm::perspectiveRH(glm::radians(45.0f), static_cast<float>(window_w)/window_h, 0.1f, 300.0f);
    program.SetUniform("uProj", proj);

    Camera camera;

    // INPUT
    bool key_states[SDL_NUM_SCANCODES]{};

    // MAIN LOOP
    float dt{};
    uint64_t start = SDL_GetPerformanceCounter();
    bool running = true;
    while(running == true)
    {
        // EVENTS HANDLING
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                
                key_states[e.key.keysym.scancode] = 1;
            }
            else if(e.type == SDL_KEYUP)
            {
                key_states[e.key.keysym.scancode] = 0;
            }
        }

        // UPDATING
        if(key_states[SDL_SCANCODE_D]) cannon.Move(22.0f *  kWorldRight * dt);
        if(key_states[SDL_SCANCODE_A]) cannon.Move(22.0f * -kWorldRight * dt);

        // invaders.Move(dt * glm::vec3(5.0f, 0, 0));
        static float accum{};
        const float move_delay = 1.0f;
        if(accum > move_delay)
        {
            invaders.Move(glm::vec3(1.5f, 0, 0));
            accum -= move_delay;
        }
        else
        {
            accum += dt;
        }

        camera.SetPosition(cannon.Position() + glm::vec3(0, 35, 38));
        camera.LookAt(cannon.Position() + glm::vec3(0, 0, -35));

        // RENDERING
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.View();
        program.SetUniform("uView", view);
        program.Use();
        invaders.Render(program);
        cannon.Render(program);

        SDL_GL_SwapWindow(window);

        // OPENGL ERROR DETECTION
        const GLenum error_code = glGetError();
        if(error_code != GL_NONE)
        {
            std::cerr << "OpenGL error. Error code: 0x" << std::hex << error_code << std::endl;
        }

        // DELTA TIME CALCULATION
        SDL_Delay(1);
        uint64_t end = SDL_GetPerformanceCounter();
        dt = static_cast<float>(end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
        start = end;
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}