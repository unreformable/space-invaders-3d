#include "Game.hpp"

#include "Graphics.hpp"



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
    }
}

void Game::Update()
{
    Graphics::CheckForErrors();

    uint64_t loop_end_ms = SDL_GetPerformanceCounter();
    m_DeltaTime = static_cast<float>(loop_end_ms - m_LoopStartMs) / static_cast<float>(SDL_GetPerformanceFrequency());
    m_LoopStartMs = loop_end_ms;
}

void Game::Render()
{
    Graphics::Clear();
    
    Graphics::Display();
}