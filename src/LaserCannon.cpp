#include "LaserCannon.hpp"

#include "CoordinateSystem.hpp"

#include "glm/ext/matrix_transform.hpp"



LaserCannon::LaserCannon()
:   m_Transform(1.0f)
{
    Bitmap3D bitmap;
    bitmap.Load("../assets/bitmaps/laser_cannon");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();
    m_Mesh.CreateFromBitmap(bitmap);
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