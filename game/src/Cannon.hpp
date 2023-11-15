#pragma once

#include "Actor.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Cannon: public Actor
{
public:
    Cannon(Game& game, const glm::vec3& position);

    virtual void Update(float dt);
    virtual void Render() const;
    virtual void OnCollisionEnter(const CollisionInfo& info);

private:
    void TryShoot();

private:
    glm::vec3 m_Position;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;

    const float m_ShootCooldown;
    const float m_VelocityX;
    float m_CurrentShootCooldown;
};