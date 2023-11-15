#pragma once

#include "Actor.hpp"
#include "Invader.hpp"



class InvadersManager: public Actor
{
public:
    static constexpr const float MIN_X = -100.0f;
    static constexpr const float MAX_X =  100.0f;

public:
    InvadersManager(Game& game, float move_down_time);

    virtual void Update(float dt);
    virtual void OnEvent(const Event& event);

private:
    const float m_MoveDownTimer;
    float m_CurrentMoveDownTimer;
    bool m_InvadersShouldMoveRight;
};