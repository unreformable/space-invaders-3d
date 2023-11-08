#include "Bitmap3D.hpp"
#include "Camera.hpp"
#include "Cannon.hpp"
#include "CoordinateSystem.hpp"
#include "Debug.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "Invaders.hpp"
#include "Program.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_clip_space.hpp"



int main()
{
    EngineProps props;
    props.m_WindowWidth = 1280;
    props.m_WindowHeight = 720;
    props.m_WindowTitle = "Space Invaders 3D";

    Engine::Initalize(props);

    Program program;
    program.Load("../../assets/shaders/model.vs", "../../assets/shaders/model.fs");

    // GAME OBJECTS
    Invaders invaders(5, 11);

    Bitmap3D laser_bitmap;
    laser_bitmap.Load("../../assets/bitmaps/laser");
    Mesh cannon_laser;
    cannon_laser.CreateFromBitmap(laser_bitmap);

    Cannon cannon;
    cannon.SetPosition({0, 0, 50});

    
    // Box limit;
    // limit.SetMin(cannon.Position() + glm::vec3(-100, -100, -300));
    // limit.SetMax(cannon.Position() + glm::vec3( 200, 100, 100));
    // lasers.SetLimit(limit);

    // CAMERA
    const glm::mat4 proj = glm::perspectiveRH(glm::radians(45.0f), static_cast<float>(props.m_WindowWidth)/props.m_WindowHeight, 0.1f, 300.0f);
    program.SetUniform("uProj", proj);

    Camera camera;

    // MAIN LOOP DATA
    bool running = true;
    Engine::SetEventCallback([&](const SDL_Event& e)
    {
        if(e.type == SDL_QUIT)
            running = false;
        if(Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
            running = false;
    });

    // MAIN LOOP
    while(running == true)
    {
        Engine::LoopBegin();

        // UPDATING
        const float dt = Engine::DeltaTime();

        cannon.Update(dt);
        invaders.Update(dt);

        camera.SetPosition(cannon.Position() + glm::vec3(0, 35, 38));
        camera.LookAt(cannon.Position() + glm::vec3(0, 0, -35));

        // RENDERING
        Engine::RenderBegin();
        {
            glm::mat4 view = camera.View();
            program.SetUniform("uView", view);
            program.Use();
            invaders.Render(program);
            cannon.Render(program);
        }
        Engine::RenderEnd();

        Engine::LoopEnd();
    }

    Engine::Terminate();
    
    return 0;
}