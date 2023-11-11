#pragma once

#include "Actor.hpp"
#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Invader: public Actor
{
public:
    Invader(Game& game, const glm::vec3& position);

    virtual void Update(float dt);
    virtual void Render() const;

private:
    glm::vec3 m_Position;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
};