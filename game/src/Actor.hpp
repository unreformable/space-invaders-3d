#pragma once

#include "Collidable.hpp"
#include "EventListener.hpp"

#include "SDL2/SDL_events.h"



class Game;

class Actor: public Collidable, public EventListener
{
public:
    Actor(Game& game);
    virtual ~Actor() = default;

    virtual void Update(float dt) {}
    virtual void Render() const {}
    virtual void OnCollisionEnter(const CollisionInfo& info) {}
    virtual void OnEvent(const Event& event) {}

protected:
    Game& m_Game;
};