#pragma once

#include "glm/vec3.hpp"



enum class EventType
{
    InvaderReachedLeftSide,
    InvaderReachedRightSide,
    InvadersChangeVelocity
};

struct EventData
{
    union
    {
        float m_Value;
        glm::vec3 m_Velocity;
    };
};

struct Event
{
    EventType m_Type;
    EventData m_Data;
};