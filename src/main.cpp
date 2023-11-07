#include "Bitmap3D.hpp"
#include "Camera.hpp"
#include "Cannon.hpp"
#include "CoordinateSystem.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "Invaders.hpp"
#include "Laser.hpp"
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
    EngineProps props;
    props.m_WindowWidth = 1280;
    props.m_WindowHeight = 720;
    props.m_WindowTitle = "Space Invaders 3D";

    Engine engine(props);

    Program program;
    program.Load("../assets/shaders/model.vs", "../assets/shaders/model.fs");

    // GAME OBJECTS
    Invaders invaders;

    Cannon cannon;
    cannon.SetPosition({0, 0, 50});

    Bitmap3D laser_bitmap;
    laser_bitmap.Load("../assets/bitmaps/laser");
    Mesh laser_mesh;
    laser_mesh.CreateFromBitmap(laser_bitmap);
    Laser laser_prefab;
    laser_prefab.SetMesh(&laser_mesh);
    
    std::vector<Laser> lasers;
    float current_shoot_delay = 0.0f;
    const float shoot_delay = 1.0f;

    // CAMERA
    const glm::mat4 proj = glm::perspectiveRH(glm::radians(45.0f), static_cast<float>(props.m_WindowWidth)/props.m_WindowHeight, 0.1f, 300.0f);
    program.SetUniform("uProj", proj);

    Camera camera;

    // INPUT
    Input input;

    // MAIN LOOP
    bool running = true;
    while(running == true)
    {
        engine.LoopBegin();

        // EVENTS HANDLING
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            input.Update(e);

            if(e.type == SDL_QUIT)
            {
                running = false;
            }
            if(input.IsKeyPressed(SDL_SCANCODE_ESCAPE))
                running = false;
        }

        // UPDATING
        const float dt = engine.DeltaTime();
        if(input.IsKeyPressed(SDL_SCANCODE_D))
        {
            cannon.Move(22.0f *  kWorldRight * dt);
        }
        if(input.IsKeyPressed(SDL_SCANCODE_A))
        {
            cannon.Move(22.0f * -kWorldRight * dt);
        }
        if(input.IsKeyPressed(SDL_SCANCODE_W))
        {
            if(current_shoot_delay <= 0.0f)
            {
                laser_prefab.SetPosition(cannon.Position());
                lasers.push_back(laser_prefab);
                
                current_shoot_delay = shoot_delay;
            }
        }

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

        current_shoot_delay -= dt;
        for(Laser& laser : lasers)
            laser.Move(dt * glm::vec3(0, 0, -25.0f));

        camera.SetPosition(cannon.Position() + glm::vec3(0, 35, 38));
        camera.LookAt(cannon.Position() + glm::vec3(0, 0, -35));

        // RENDERING
        engine.RenderBegin();
        {
            glm::mat4 view = camera.View();
            program.SetUniform("uView", view);
            program.Use();
            laser_prefab.Prepare();
            for(const Laser& laser : lasers)
                laser.Render(program);
            invaders.Render(program);
            cannon.Render(program);
        }
        engine.RenderEnd();

        engine.LoopEnd();
    }
    
    return 0;
}