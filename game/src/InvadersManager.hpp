#pragma once

#include "Actor.hpp"
#include "Invader.hpp"



class InvadersManager: public Actor
{
public:
    static constexpr const float MIN_X = -105.0f;
    static constexpr const float MAX_X =  105.0f;

public:
    InvadersManager(Game& game, const glm::vec3& position);

    virtual void Update(float dt);
    virtual void OnEvent(const Event& event);

private:
    void InvadersMoveRight();
    void InvadersMoveLeft();
    void InvadersMoveDown();

private:
    float m_InvadersVelocityX;
    float m_InvadersVelocityZ;

    const float m_MoveDownTimer;
    float m_CurrentMoveDownTimer;
    bool m_InvadersMoveRight;
};