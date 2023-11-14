#pragma once

#include "Event.hpp"
#include "Input.hpp"
#include "PhysicsSystem.hpp"
#include "RenderSystem.hpp"

#include <list>



class Actor;

class Game
{
public:
    Game();
    ~Game();
    
    void Run();

    void InvokeEvent(Event event);

    inline RenderSystem* GetRenderSystem() { return &m_RenderSystem; }
    inline PhysicsSystem* GetPhysicsSystem() { return &m_PhysicsSystem; }
    inline const Input* GetInput() { return &m_Input; }

private:
    void InitalizeRenderSystem();
    void InitalizeActors();

    void HandleInput();
    void Update();
    void Render();

private:
    Actor* m_Root;
    
    std::list<Event> m_EventsToInvoke;

    Input m_Input;

    PhysicsSystem m_PhysicsSystem;
    RenderSystem m_RenderSystem;
    Program* m_Program;

    float m_DeltaTime;
    float m_LoopStartMs;

    bool m_Running;
};