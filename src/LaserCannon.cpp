#include "LaserCannon.hpp"

#include "CoordinateSystem.hpp"

#include "glm/ext/matrix_transform.hpp"



LaserCannon::LaserCannon()
{
    Bitmap3D bitmap;
    bitmap.Load("../assets/bitmaps/laser_cannon");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();
    m_Mesh.CreateFromBitmap(bitmap);

    m_Transform = glm::mat4(1.0f);
    m_Transform = glm::rotate(m_Transform, glm::radians(-90.0f), kWorldRight);
}

void LaserCannon::SetPosition(const glm::vec3& position)
{
    m_Transform[3].x = position.x;
    m_Transform[3].y = position.y;
    m_Transform[3].z = position.z;
}

void LaserCannon::Move(const glm::vec3& distance)
{
    m_Transform[3].x += distance.x;
    m_Transform[3].y += distance.y;
    m_Transform[3].z += distance.z;
}

void LaserCannon::Render(const Program& program) const
{
    program.SetUniform("uWorld", m_Transform);
    m_Mesh.Prepare();
    m_Mesh.Render(0);
}