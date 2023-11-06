#include "Laser.hpp"



Laser::Laser()
:   m_Transform(1.0f)
{
}

void Laser::Move(const glm::vec3& distance)
{
    m_Transform[3].x += distance.x;
    m_Transform[3].y += distance.y;
    m_Transform[3].z += distance.z;
}

void Laser::Prepare() const
{
    m_Mesh->Prepare();
}

void Laser::Render(const Program& program) const
{
    program.SetUniform("uWorld", m_Transform);
    m_Mesh->Render(0);
}

void Laser::SetPosition(const glm::vec3& position)
{
    m_Transform[3].x = position.x;
    m_Transform[3].y = position.y;
    m_Transform[3].z = position.z;
}