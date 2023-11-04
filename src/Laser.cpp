#include "Laser.hpp"



Laser::Laser()
:   m_Transform(1.0f)
{
}

void Laser::Move(const glm::vec3& distance)
{

}

void Laser::Prepare()
{
    m_Mesh->Prepare();
}

void Laser::Render(const Program& program)
{
    program.SetUniform("uWorld", m_Transform);
    m_Mesh->Render(0);
}