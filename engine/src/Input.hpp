#pragma once

#include "SDL2/SDL_events.h"



class Input
{
public:
    Input();

    void Update(const SDL_Event& event);

    inline bool IsKeyPressed(SDL_Scancode key) { return m_KeyStates[key] == 1; }

private:
    Input(const Input& other);
    Input& operator=(const Input& other);
    Input(Input&& other);
    Input& operator=(Input&& other);

private:
    int m_KeyStates[SDL_NUM_SCANCODES];
};