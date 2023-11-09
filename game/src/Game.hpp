#pragma once

#include "Input.hpp"
#include "RenderSystem.hpp"

#include <memory>
#include <vector>



class Actor;

class Game
{
public:
    Game();
    ~Game();
    void Run();

    RenderSystem* GetRenderSystem() { return &m_RenderSystem; }
    const Input* GetInput() { return &m_Input; }

private:
    void InitalizeRenderSystem();
    void InitalizeActors();

    void HandleInput();
    void Update();
    void Render();

private:
    std::vector<std::unique_ptr<Actor>> m_Actors;

    Input m_Input;

    RenderSystem m_RenderSystem;
    Program* m_Program;

    float m_DeltaTime;
    float m_LoopStartMs;

    bool m_Running;
};