#pragma once

#include "Lasers.hpp"
#include "Mesh.hpp"
#include "Program.hpp"

#include "glm/vec3.hpp"



class Cannon
{
public:
    Cannon(Lasers& lasers);

    void Update(float dt);
    void Render(const Program& program) const;

    void SetPosition(const glm::vec3& position);
    glm::vec3 Position() const { return glm::vec3(m_Transform[3]); }

private:
    void Move(const glm::vec3& distance);

private:
    glm::mat4 m_Transform;
    Mesh m_Mesh;

    float m_CurrentShootDelay = 0.0f;
    const float m_ShootDelay = 1.0f;
    Mesh m_Laser;
    Lasers& m_Lasers;
};