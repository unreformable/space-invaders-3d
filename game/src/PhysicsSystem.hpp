#pragma once

#include "Box.hpp"
#include "Tag.hpp"

#include <vector>



class Actor;

class PhysicsSystem
{
public:
    PhysicsSystem();

    uint32_t CreatePhysicsComponent(Actor& actor);
    
    void CheckCollisions();

    void SetPositionReference(uint32_t id, glm::vec3& position);
    void SetTag(uint32_t id, Tag tag);
    void SetBoundingBox(uint32_t id, const Box& bounding_box);    

private:
    std::vector<glm::vec3*> m_Positions;
    std::vector<Tag> m_Tags;
    std::vector<Box> m_BoundingBoxes;
    std::vector<Actor*> m_Actors;
    uint32_t m_NextId;
};

class PhysicsComponent
{
public:
    friend class PhysicsSystem;

public:
    PhysicsComponent(PhysicsSystem& system, Actor& actor);

    inline void SetPositionReference(glm::vec3& position) { m_System.SetPositionReference(m_Id, position); }
    inline void SetTag(Tag tag) { m_System.SetTag(m_Id, tag); }
    inline void SetBoundingBox(const Box& bounding_box) { m_System.SetBoundingBox(m_Id, bounding_box); }

private:
    PhysicsSystem& m_System;
    uint32_t m_Id;
};