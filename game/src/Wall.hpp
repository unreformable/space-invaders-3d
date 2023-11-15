#pragma once

#include "Actor.hpp"
#include "Box.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Wall: public Actor
{
public:
    Wall(Game& game, const glm::vec3& position);

    virtual void Render() const;
    virtual void OnCollisionEnter(const CollisionInfo& info);

private:
    glm::vec3 m_Position;
    uint32_t m_Health;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
};