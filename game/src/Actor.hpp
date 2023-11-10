#pragma once

#include "Collidable.hpp"

#include "SDL2/SDL_events.h"



class Game;

class Actor: public Collidable
{
public:
    Actor(Game& game);
    virtual ~Actor() = default;

    virtual void Update(float dt) {}
    virtual void Render() const {}

protected:
    Game& m_Game;
};