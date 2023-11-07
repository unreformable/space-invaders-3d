#pragma once

#include "Mesh.hpp"
#include "Program.hpp"

#include "glm/mat4x4.hpp"

#include <unordered_map>



class Lasers
{
public:
    void Create(const glm::mat4& transform, const glm::vec3& velocity, const Mesh* mesh);
    void Update(float dt);
    void Render(const Program& program);

    void SetLimit(const Box& limit) { m_Limit = limit; }

private:
    Box m_Limit;
    std::vector<const Mesh*> m_Meshes;
    std::unordered_map<uint32_t, std::vector<glm::mat4>> m_Transforms;
    std::unordered_map<uint32_t, std::vector<glm::vec3>> m_Velocities;
};