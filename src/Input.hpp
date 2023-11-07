#pragma once

#include "SDL2/SDL_events.h"



class Input
{
public:
    static void Update(const SDL_Event& event);

    static inline bool IsKeyPressed(SDL_Scancode key) { return m_KeyStates[key] == 1; }

private:
    Input(const Input& other);
    Input& operator=(const Input& other);
    Input(Input&& other);
    Input& operator=(Input&& other);

private:
    static int m_KeyStates[SDL_NUM_SCANCODES];
};