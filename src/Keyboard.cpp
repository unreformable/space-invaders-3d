#include "Keyboard.hpp"



namespace Keyboard
{
    int key_states[SDL_NUM_SCANCODES]{};

    void Update(const SDL_KeyboardEvent& keyboard_event)
    {
        if(keyboard_event.type == SDL_KEYDOWN)
        {
            key_states[keyboard_event.keysym.scancode] = 1;
        }
        if(keyboard_event.type == SDL_KEYUP)
        {
            key_states[keyboard_event.keysym.scancode] = 0;
        }
    }

    bool IsKeyPressed(SDL_Scancode scancode)
    {
        return key_states[scancode] == 1;
    }
}