#include "PhysicsSystem.hpp"

#include "Actor.hpp"
#include "Debug.hpp"
#include "Utils.hpp"

#include <iostream>




PhysicsSystem::PhysicsSystem()
:   m_NextId{}
{
}

uint32_t PhysicsSystem::CreatePhysicsComponent(Actor& actor)
{
    m_Positions.push_back({});
    m_Tags.push_back({});
    m_BoundingBoxes.push_back({});
    m_Actors.push_back(&actor);

    return m_NextId++;
}

void PhysicsSystem::SetPositionReference(uint32_t id, glm::vec3& position)
{
    m_Positions[id] = &position;
}

void PhysicsSystem::SetTag(uint32_t id, const uint32_t& tag)
{
    m_Tags[id] = tag;
}

void PhysicsSystem::SetBoundingBox(uint32_t id, const Box& bounding_box)
{
    m_BoundingBoxes[id] = bounding_box;
}

void PhysicsSystem::CheckCollisions()
{
    for(uint32_t i = 0; i < m_Positions.size(); i++)
    {
        const glm::vec3& pos1 = *m_Positions[i];
        const Box& box1 = m_BoundingBoxes[i];

        for(uint32_t j = 0; j < m_Positions.size(); j++)
        {
            if(i == j)
                continue;
            
            if(Utils::Collides(pos1, box1, *m_Positions[j], m_BoundingBoxes[j]))
            {
                std::cerr << i;

                // Make collision info for actor that we collided with
            }
        }
    }
}

PhysicsComponent::PhysicsComponent(PhysicsSystem& system, Actor& actor)
:   m_System(system)
{
    m_Id = system.CreatePhysicsComponent(actor);
}