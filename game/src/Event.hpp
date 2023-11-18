#pragma once

#include "glm/vec3.hpp"



enum class EventType
{
    InvaderReachedLeftSide,
    InvaderReachedRightSide,
    InvadersChangeVelocity,
    InvaderDied,
    UfoDied,
    InvadersChangeFrame
};

struct EventData
{
    union
    {
        uint32_t m_MeshFrame;
        glm::vec3 m_Velocity;
    };
};

struct Event
{
    EventType m_Type;
    EventData m_Data;
};