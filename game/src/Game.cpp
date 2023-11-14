#include "Game.hpp"

#include "Cannon.hpp"
#include "Graphics.hpp"
#include "InvadersManager.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <algorithm>



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
    
    m_Root = new Actor(*this);

    InitalizeActors();

    m_LoopStartMs = SDL_GetPerformanceCounter();
}

Game::~Game()
{
    delete m_Root;
    
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

void Game::InvokeEvent(Event event)
{
    m_EventsToInvoke.push_back(event);
}

void Game::InitalizeRenderSystem()
{
    // Cannon assets
    {
        Bitmap3D* cannon_bitmap = m_RenderSystem.CreateBitmap("cannon");
        cannon_bitmap->CreateFromFile("../../assets/bitmaps/cannon");
        cannon_bitmap->ReverseEachFrame();
        
        Mesh* cannon_mesh = m_RenderSystem.CreateMesh("cannon");
        cannon_mesh->CreateFromBitmap(*cannon_bitmap);
    }

    // Small invader assets
    {
        Bitmap3D* cannon_bitmap = m_RenderSystem.CreateBitmap("small_invader");
        cannon_bitmap->CreateFromFile("../../assets/bitmaps/small_invader");
        cannon_bitmap->ReverseEachFrame();
        
        Mesh* cannon_mesh = m_RenderSystem.CreateMesh("small_invader");
        cannon_mesh->CreateFromBitmap(*cannon_bitmap);
    }

    // Laser assets
    {
        Bitmap3D* laser_bitmap = m_RenderSystem.CreateBitmap("laser");
        laser_bitmap->CreateFromFile("../../assets/bitmaps/laser");
        laser_bitmap->ReverseEachFrame();

        Mesh* laser_mesh = m_RenderSystem.CreateMesh("laser");
        laser_mesh->CreateFromBitmap(*laser_bitmap);
    }

    m_Program = m_RenderSystem.CreateProgram("mesh");
    m_Program->CreateFromFiles("../../assets/shaders/mesh.vs", "../../assets/shaders/mesh.fs");
}

void Game::InitalizeActors()
{
    Actor* cannon = new Cannon(*this, {0, 0, 0});
    Actor* invaders_manager = new InvadersManager(*this, 0.9f);

    cannon->SetParent(m_Root);
    invaders_manager->SetParent(m_Root);
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

    m_Root->CheckRemoveChildren();
    m_Root->CheckAddActors();

    for(Event event : m_EventsToInvoke)
        m_Root->OnEvent(event);
    m_EventsToInvoke.clear();

    m_Root->Update(m_DeltaTime);
    
    // Should be called every fixed time (but we go for stable FPS, so it's not that important)
    m_PhysicsSystem.CheckCollisions();

    Graphics::CheckForErrors();
}

void Game::Render()
{
    Graphics::Clear();

    m_Program->Use();
    m_Program->SetUniform("uView", glm::lookAtRH(glm::vec3(0, 45, 35), glm::vec3(0, 0, -30), glm::vec3(0, 1, 0)));
    m_Program->SetUniform("uProj", glm::perspectiveRH(glm::radians(45.0f), 16.0f/9, 0.1f, 250.0f));

    m_Root->Render();
    
    Graphics::Display();
}