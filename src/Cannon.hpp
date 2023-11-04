#pragma once

#include "Mesh.hpp"
#include "Program.hpp"

#include "glm/vec3.hpp"



class Cannon
{
public:
    Cannon();

    void SetPosition(const glm::vec3& position);
    void Move(const glm::vec3& distance);
    void Render(const Program& program) const;

    glm::vec3 Position() const { return glm::vec3(m_Transform[3]); }

private:
    glm::mat4 m_Transform;
    Mesh m_Mesh;
};