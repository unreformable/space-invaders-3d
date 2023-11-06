#pragma once

#include "SDL2/SDL_events.h"



namespace Keyboard
{
    void Update(const SDL_KeyboardEvent& keyboard_event);

    bool IsKeyPressed(SDL_Scancode scancode);
}