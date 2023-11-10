#include "PhysicsSystem.hpp"

#include "Actor.hpp"

#include <iostream>




PhysicsSystem::PhysicsSystem()
:   m_NextId{}
{
}

uint32_t PhysicsSystem::CreatePhysicsComponent(Actor& actor)
{
    m_Positions.push_back({});
    m_Velocities.push_back({});
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
    std::cerr << "Implement CheckCollisions() in PhysicsSystem" << std::endl;
}

PhysicsComponent::PhysicsComponent(PhysicsSystem& system, Actor& actor)
:   m_System(system)
{
    m_Id = system.CreatePhysicsComponent(actor);
}