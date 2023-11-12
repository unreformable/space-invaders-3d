#pragma once

#include "Actor.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Invader: public Actor
{
public:
    Invader(Game& game, const glm::vec3& position, const glm::vec3& velocity);

    virtual void Update(float dt);
    virtual void Render() const;
    virtual void OnEvent(const Event& event);

private:
    glm::vec3 m_Position;
    glm::vec3 m_Velocity;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
};