#include "Game.hpp"

#include "InvadersManager.hpp"
#include "Laser.hpp"
#include "Cannon.hpp"
#include "Graphics.hpp"
#include "Invader.hpp"
#include "Tag.hpp"
#include "UfoSpawner.hpp"
#include "Wall.hpp"

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
    InitalizeActors();

    m_LoopStartMs = SDL_GetPerformanceCounter();
}

Game::~Game()
{
    for(Actor* actor : m_Actors)
        delete actor;
    
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

void Game::AddActor(Actor* actor)
{
    m_ActorsToAdd.push_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
    m_ActorsToRemove.push_back(actor);
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

    // Wall assets
    {
        Bitmap3D* wall_bitmap = m_RenderSystem.CreateBitmap("wall");
        wall_bitmap->CreateFromFile("../../assets/bitmaps/wall");
        wall_bitmap->ReverseEachFrame();
        
        Mesh* wall_mesh = m_RenderSystem.CreateMesh("wall");
        wall_mesh->CreateFromBitmap(*wall_bitmap);
    }

    // Ufo assets
    {
        Bitmap3D* wall_bitmap = m_RenderSystem.CreateBitmap("ufo");
        wall_bitmap->CreateFromFile("../../assets/bitmaps/ufo");
        wall_bitmap->ReverseEachFrame();
        
        Mesh* wall_mesh = m_RenderSystem.CreateMesh("ufo");
        wall_mesh->CreateFromBitmap(*wall_bitmap);
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
    AddActor(new Cannon(*this, {0, 0, 0}));
    AddActor(new Wall(*this, {-60, 0, -18}));
    AddActor(new Wall(*this, {-20, 0, -18}));
    AddActor(new Wall(*this, { 20, 0, -18}));
    AddActor(new Wall(*this, { 60, 0, -18}));
    AddActor(new InvadersManager(*this, {InvadersManager::MIN_X+1, 0, -100}));
    AddActor(new UfoSpawner(*this, {InvadersManager::MIN_X-20, 0, -160}, {8, 0, 0}, -InvadersManager::MIN_X+20));
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

    for(Actor* actor : m_ActorsToAdd)
        m_Actors.push_back(actor);
    m_ActorsToAdd.clear();

    for(Actor* actor: m_ActorsToRemove)
    {
        auto it = std::find(std::begin(m_Actors), std::end(m_Actors), actor);
        delete actor;

        *it = m_Actors.back();
        m_Actors.pop_back();
    }
    m_ActorsToRemove.clear();

    for(Event event : m_EventsToInvoke)
        for(Actor* actor : m_Actors)
            actor->OnEvent(event);
    m_EventsToInvoke.clear();

    for(Actor* actor : m_Actors)
        actor->Update(m_DeltaTime);
    
    // Should be called every fixed time (but we go for stable FPS, so it's not that important)
    m_PhysicsSystem.CheckCollisions();

    Graphics::CheckForErrors();
}

void Game::Render()
{
    Graphics::Clear();

    const float fov = glm::radians(60.0f);
    const glm::vec3 view_pos = glm::vec3(0, 75, 20);
    const glm::vec3 look_at = glm::vec3(0, 0, -45);
    const float aspect_ratio = 1280.0f/720.0f;
    const float near_plane = 0.1f;
    const float far_plane  = 250.0f;

    m_Program->Use();
    m_Program->SetUniform("uView", glm::lookAtRH(view_pos, look_at, glm::vec3(0, 1, 0)));
    m_Program->SetUniform("uProj", glm::perspectiveRH(fov, aspect_ratio, near_plane, far_plane));

    for(Actor* actor : m_Actors)
        actor->Render();
    
    Graphics::Display();
}