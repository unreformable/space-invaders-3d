#pragma once

#include "Mesh.hpp"
#include "Program.hpp"

#include "glm/vec3.hpp"



class Laser
{
public:
    Laser();

    void Move(const glm::vec3& distance);
    void Prepare();
    void Render(const Program& program);

    inline void SetMesh(const Mesh* mesh) { m_Mesh = mesh; }

private:
    glm::mat4 m_Transform;
    const Mesh* m_Mesh;
};