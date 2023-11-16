#include "InvadersManager.hpp"

#include "Event.hpp"
#include "Game.hpp"
#include "Invader.hpp"



InvadersManager::InvadersManager(Game& game)
:   Actor(game),
    m_InvadersVelocityX(12),
    m_InvadersVelocityZ(9),
    m_MoveDownTimer(0.9f),
    m_InvadersMoveRight(true)
{
    const float x_start = MIN_X+1;
    const float y_start = 0;
    const float z_start = -100;

    for(int z = 0; z < 5; z++)
    {
        for(int x = 0; x < 11; x++)
        {
            const float x_adjust =  13 * x;
            const float z_adjust = -13 * z;

            const glm::vec3 invader_pos = glm::vec3(
                x_start + x_adjust,
                y_start,
                z_start + z_adjust
            );
            game.AddActor(new Invader(game, invader_pos));
        }
    }

    InvadersMoveRight();
}

void InvadersManager::Update(float dt)
{
    if(m_CurrentMoveDownTimer > 0.0f)
    {
        m_CurrentMoveDownTimer -= dt;

        if(m_CurrentMoveDownTimer <= 0.0f)
        {
            if(m_InvadersMoveRight)
                InvadersMoveRight();
            else
                InvadersMoveLeft();
        }
    }
}

void InvadersManager::OnEvent(const Event& event)
{
    if(event.m_Type == EventType::InvaderDied)
    {
        m_InvadersVelocityX += 0.2f;
        m_InvadersVelocityZ += 0.15f;
    }
    if(event.m_Type == EventType::InvaderReachedLeftSide)
    {
        if(m_InvadersMoveRight == true)
            return;

        InvadersMoveDown();

        m_CurrentMoveDownTimer = m_MoveDownTimer;
        m_InvadersMoveRight = true;
    }
    else if(event.m_Type == EventType::InvaderReachedRightSide)
    {
        if(m_InvadersMoveRight == false)
            return;
        
        InvadersMoveDown();

        m_CurrentMoveDownTimer = m_MoveDownTimer;
        m_InvadersMoveRight = false;
    }
}

void InvadersManager::InvadersMoveRight()
{
    Event event;
    event.m_Type = EventType::InvadersChangeVelocity;
    event.m_Data.m_Velocity = {m_InvadersVelocityX, 0, 0};
    m_Game.InvokeEvent(event);
}

void InvadersManager::InvadersMoveLeft()
{
    Event event;
    event.m_Type = EventType::InvadersChangeVelocity;
    event.m_Data.m_Velocity = {-m_InvadersVelocityX, 0, 0};
    m_Game.InvokeEvent(event);
}

void InvadersManager::InvadersMoveDown()
{
    Event event;
    event.m_Type = EventType::InvadersChangeVelocity;
    event.m_Data.m_Velocity = {0, 0, m_InvadersVelocityZ};
    m_Game.InvokeEvent(event);
}