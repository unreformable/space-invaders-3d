#include "Game.hpp"

#include "Cannon.hpp"
#include "Graphics.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"



Game::Game()
:   m_DeltaTime{},
    m_Running(false)
{
    Graphics::Config config;
    config.m_WindowWidth = 1280;
    config.m_WindowHeight = 720;
    config.m_WindowTitle = "Space Invaders 3D";
    config.m_ClearColor = { 0.1f, 0.1f, 0.1f, 1.0f };

    Graphics::Initalize(config);

    InitalizeRenderSystem();
    InitalizeActors();

    m_LoopStartMs = SDL_GetPerformanceCounter();
}

Game::~Game()
{
    Graphics::Terminate();
}

void Game::Run()
{
    //Graphics::PinMouseToWindowCenter();

    m_Running = true;
    while(m_Running)
    {
        HandleInput();

        Update();
        Render();
    }
}

void Game::InitalizeRenderSystem()
{    
    Bitmap3D cannon_bitmap;
    cannon_bitmap.CreateFromFile("../../assets/bitmaps/cannon");
    cannon_bitmap.ReverseEachFrame();
    
    Mesh* cannon_mesh = GetRenderSystem()->CreateMesh("cannon");
    cannon_mesh->CreateFromBitmap(cannon_bitmap);

    m_Program = GetRenderSystem()->CreateProgram("mesh");
    m_Program->CreateFromFiles("../../assets/shaders/mesh.vs", "../../assets/shaders/mesh.fs");
}

void Game::InitalizeActors()
{
    m_Actors.emplace_back(new Cannon(*this));
}

void Game::HandleInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            m_Running = false;
        }
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE)
                m_Running = false;
        }

        m_Input.Update(e);
    }

}

void Game::Update()
{
    uint64_t loop_end_ms = SDL_GetPerformanceCounter();
    m_DeltaTime = static_cast<float>(loop_end_ms - m_LoopStartMs) / static_cast<float>(SDL_GetPerformanceFrequency());
    m_LoopStartMs = loop_end_ms;

    for(std::unique_ptr<Actor>& actor : m_Actors)
        actor->Update(m_DeltaTime);

    Graphics::CheckForErrors();
}

void Game::Render()
{
    Graphics::Clear();

    m_Program->Use();
    m_Program->SetUniform("uView", glm::lookAtRH(glm::vec3(0, 20, 10), glm::vec3(0, 0, -30), glm::vec3(0, 1, 0)));
    m_Program->SetUniform("uProj", glm::perspectiveRH(glm::radians(45.0f), 16.0f/9, 0.1f, 100.0f));

    for(std::unique_ptr<Actor>& actor : m_Actors)
        actor->Render();
    
    Graphics::Display();
}