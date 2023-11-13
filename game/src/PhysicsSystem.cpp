#include "PhysicsSystem.hpp"

#include "Actor.hpp"
#include "Debug.hpp"
#include "Utils.hpp"

#include <iostream>



uint32_t PhysicsSystem::AddPhysicsComponent(PhysicsComponent* component, Actor& actor)
{
    m_Positions.push_back({});
    m_Tags.push_back({});
    m_BoundingBoxes.push_back({});
    m_PhysicsComponents.push_back(component);
    m_Actors.push_back(&actor);

    return m_Positions.size() - 1;
}

void PhysicsSystem::RemovePhysicsComponent(uint32_t id)
{
    const int last_used_id = m_Positions.size() - 1;

    if(last_used_id >= 0)
    {
        m_Positions[id] = m_Positions[last_used_id];
        m_Tags[id] = m_Tags[last_used_id];
        m_BoundingBoxes[id] = m_BoundingBoxes[last_used_id];
        m_PhysicsComponents[id] = m_PhysicsComponents[last_used_id];
        m_Actors[id] = m_Actors[last_used_id];

        m_PhysicsComponents[id]->m_Id = id;
    }

    m_Positions.pop_back();
    m_Tags.pop_back();
    m_BoundingBoxes.pop_back();
    m_PhysicsComponents.pop_back();
    m_Actors.pop_back();
}

void PhysicsSystem::SetPositionReference(uint32_t id, glm::vec3& position)
{
    m_Positions[id] = &position;
}

void PhysicsSystem::SetTag(uint32_t id, Tag tag)
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
                CollisionInfo info;
                info.m_TargetTag = m_Tags[j];
                info.m_Target = m_Actors[j];

                m_Actors[i]->OnCollisionEnter(info);
            }
        }
    }
}

PhysicsComponent::PhysicsComponent(PhysicsSystem& system, Actor& actor)
:   m_System(system)
{
    m_Id = system.AddPhysicsComponent(this, actor);
}

PhysicsComponent::~PhysicsComponent()
{
    m_System.RemovePhysicsComponent(m_Id);
}