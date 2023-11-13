#pragma once

#include "Actor.hpp"



class InvadersManager: public Actor
{
public:
    static constexpr const float MIN_X = -90.0f;
    static constexpr const float MAX_X =  90.0f;

public:
    InvadersManager(Game& game, float move_down_time);

    virtual void Update(float dt);
    virtual void OnEvent(const Event& event);

private:
    const float m_MoveDownTime;
    float m_CurrentMoveDownTime;
    bool m_InvadersShouldMoveRight;
};