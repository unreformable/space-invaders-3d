#pragma once

#include "Input.hpp"
#include "PhysicsSystem.hpp"
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
    PhysicsSystem* GetPhysicsSystem() { return &m_PhysicsSystem; }
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

    PhysicsSystem m_PhysicsSystem;
    RenderSystem m_RenderSystem;
    Program* m_Program;

    float m_DeltaTime;
    float m_LoopStartMs;

    bool m_Running;
};