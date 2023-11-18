#pragma once

#include "Actor.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Ufo: public Actor
{
public:
    Ufo(Game& game, const glm::vec3& position, const glm::vec3& velocity, float target_position_x);

    virtual void Update(float dt);
    virtual void Render() const;
    virtual void OnCollisionEnter(const CollisionInfo& info);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Velocity;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
    float m_TargetPositionX;
};