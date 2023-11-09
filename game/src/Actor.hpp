#pragma once

#include "SDL2/SDL_events.h"



class Game;

class Actor
{
public:
    Actor(Game& game);
    virtual ~Actor() = default;

    virtual void Update(float dt) = 0;
    virtual void Render() const = 0;

protected:
    Game& m_Game;
};