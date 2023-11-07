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

#include "glm/ext/matrix_clip_space.hpp"



int main()
{
    EngineProps props;
    props.m_WindowWidth = 1280;
    props.m_WindowHeight = 720;
    props.m_WindowTitle = "Space Invaders 3D";

    Engine::Initalize(props);

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
        if(Input::IsKeyPressed(SDL_SCANCODE_W))
        {
            if(current_shoot_delay <= 0.0f)
            {
                laser_prefab.SetPosition(cannon.Position());
                lasers.push_back(laser_prefab);
                
                current_shoot_delay = shoot_delay;
            }
        }

        invaders.Update(dt);

        current_shoot_delay -= dt;
        for(Laser& laser : lasers)
            laser.Move(dt * glm::vec3(0, 0, -25.0f));

        camera.SetPosition(cannon.Position() + glm::vec3(0, 35, 38));
        camera.LookAt(cannon.Position() + glm::vec3(0, 0, -35));

        // RENDERING
        Engine::RenderBegin();
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
        Engine::RenderEnd();

        Engine::LoopEnd();
    }

    Engine::Terminate();
    
    return 0;
}