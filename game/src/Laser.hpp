#pragma once

#include "Actor.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Laser: public Actor
{
public:
    Laser(Game& game, const glm::vec3& position, const glm::vec3& velocity, uint8_t collision_layer);

    virtual void Update(float dt);
    virtual void Render() const;
    virtual void OnCollisionEnter(const CollisionInfo& info);

private:
    glm::vec3 m_Position;
    const glm::vec3 m_Velocity;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
};