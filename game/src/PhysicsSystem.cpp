#include "PhysicsSystem.hpp"

#include "Actor.hpp"
#include "Debug.hpp"
#include "Utils.hpp"

#include <iostream>



uint32_t PhysicsSystem::AddPhysicsComponent(PhysicsComponent* component, Actor& actor)
{
    m_Positions.push_back({});
    m_Layers.push_back({});
    m_Masks.push_back({});
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
        m_Layers[id] = m_Layers[last_used_id];
        m_Masks[id] = m_Masks[last_used_id];
        m_BoundingBoxes[id] = m_BoundingBoxes[last_used_id];
        m_PhysicsComponents[id] = m_PhysicsComponents[last_used_id];
        m_Actors[id] = m_Actors[last_used_id];

        m_PhysicsComponents[id]->m_Id = id;
    }

    m_Positions.pop_back();
    m_Layers.pop_back();
    m_Masks.pop_back();
    m_BoundingBoxes.pop_back();
    m_PhysicsComponents.pop_back();
    m_Actors.pop_back();
}

void PhysicsSystem::SetPositionReference(uint32_t id, glm::vec3& position)
{
    m_Positions[id] = &position;
}

void PhysicsSystem::SetLayer(uint32_t id, uint8_t layer)
{
    m_Layers[id] = layer;
}

void PhysicsSystem::SetMask(uint32_t id, uint8_t mask)
{
    m_Masks[id] = mask;
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
                const uint8_t bit_result = m_Layers[i] & m_Masks[j];

                for(uint8_t k = 0; k < 8; k++)
                {
                    if(bit_result & (1 << k))
                    {
                        CollisionInfo info;
                        info.m_Target = m_Actors[j];

                        m_Actors[i]->OnCollisionEnter(info);
                    }
                }
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