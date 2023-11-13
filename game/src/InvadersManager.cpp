#include "InvadersManager.hpp"

#include "Event.hpp"
#include "Game.hpp"
#include "Invader.hpp"



InvadersManager::InvadersManager(Game& game, float move_down_time)
:   Actor(game),
    m_MoveDownTime(move_down_time),
    m_InvadersShouldMoveRight(true)
{
    for(int z = 0; z < 5; z++)
    {
        for(int x = 0; x < 11; x++)
        {
            game.AddActor(new Invader(game, {MIN_X+1 + 13*x, 0, -90 + -13*z}));
        }
    }

    Event event;
    event.m_Type = EventType::InvadersChangeVelocity;
    event.m_Data.m_Velocity = {12, 0, 0};
    m_Game.InvokeEvent(event);
}

void InvadersManager::Update(float dt)
{
    if(m_CurrentMoveDownTime > 0.0f)
    {
        m_CurrentMoveDownTime -= dt;

        if(m_CurrentMoveDownTime <= 0.0f)
        {
            Event event;
            event.m_Type = EventType::InvadersChangeVelocity;

            if(m_InvadersShouldMoveRight)
                event.m_Data.m_Velocity = {12, 0, 0};
            else
                event.m_Data.m_Velocity = {-12, 0, 0};
            
            m_Game.InvokeEvent(event);
        }
    }
}

void InvadersManager::OnEvent(const Event& event)
{
    if(event.m_Type == EventType::InvaderReachedLeftSide)
    {
        if(m_InvadersShouldMoveRight == true)
            return;
        
        Event event;
        event.m_Type = EventType::InvadersChangeVelocity;
        event.m_Data.m_Velocity = {0, 0, 7};
        m_Game.InvokeEvent(event);

        m_CurrentMoveDownTime = m_MoveDownTime;
        m_InvadersShouldMoveRight = true;
    }
    if(event.m_Type == EventType::InvaderReachedRightSide)
    {
        if(m_InvadersShouldMoveRight == false)
            return;
        
        Event event;
        event.m_Type = EventType::InvadersChangeVelocity;
        event.m_Data.m_Velocity = {0, 0, 7};
        m_Game.InvokeEvent(event);

        m_CurrentMoveDownTime = m_MoveDownTime;
        m_InvadersShouldMoveRight = false;
    }
}