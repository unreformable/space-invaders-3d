#pragma once

#include "SDL2/SDL_events.h"



class Input
{
public:
    void Update(const SDL_Event& event);

    inline bool IsKeyPressed(SDL_Scancode key) const { return m_KeyStates[key] == 1; }

private:
    int m_KeyStates[SDL_NUM_SCANCODES]{};
};