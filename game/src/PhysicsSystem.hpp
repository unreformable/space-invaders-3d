#pragma once

#include "Box.hpp"
#include "Tag.hpp"

#include <vector>



class Actor;
class PhysicsComponent;

class PhysicsSystem
{
public:
    uint32_t AddPhysicsComponent(PhysicsComponent* component, Actor& actor);
    void RemovePhysicsComponent(uint32_t id);
    
    void CheckCollisions();

    void SetPositionReference(uint32_t id, glm::vec3& position);
    void SetLayer(uint32_t id, uint8_t layer);
    void SetMask(uint32_t id, uint8_t mask);
    void SetBoundingBox(uint32_t id, const Box& bounding_box);    

private:
    std::vector<glm::vec3*> m_Positions;
    std::vector<uint32_t> m_Layers;
    std::vector<uint32_t> m_Masks;
    std::vector<Box> m_BoundingBoxes;
    std::vector<PhysicsComponent*> m_PhysicsComponents;
    std::vector<Actor*> m_Actors;
};

class PhysicsComponent
{
public:
    friend class PhysicsSystem;

public:
    PhysicsComponent(PhysicsSystem& system, Actor& actor);
    ~PhysicsComponent();

    inline void SetPositionReference(glm::vec3& position) { m_System.SetPositionReference(m_Id, position); }
    inline void SetLayer(uint32_t layer) { m_System.SetLayer(m_Id, layer); }
    inline void SetMask(uint32_t mask) { m_System.SetMask(m_Id, mask); }
    inline void SetBoundingBox(const Box& bounding_box) { m_System.SetBoundingBox(m_Id, bounding_box); }

private:
    PhysicsSystem& m_System;
    uint32_t m_Id;
};