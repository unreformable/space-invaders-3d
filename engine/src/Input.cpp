#include "Input.hpp"



Input::Input()
:   m_KeyStates{}
{
}

void Input::Update(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        m_KeyStates[event.key.keysym.scancode] = 1;
    }
    if(event.type == SDL_KEYUP)
    {
        m_KeyStates[event.key.keysym.scancode] = 0;
    }
}