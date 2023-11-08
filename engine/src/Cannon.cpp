#include "Cannon.hpp"

#include "CoordinateSystem.hpp"
#include "Input.hpp"

#include "glm/ext/matrix_transform.hpp"



Cannon::Cannon()
:   m_Transform(1.0f),
    m_ShootDelay(1.0f)
{
    Bitmap3D bitmap;
    bitmap.Load("../../assets/bitmaps/laser_cannon");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();
    m_Mesh.CreateFromBitmap(bitmap);
}

void Cannon::Update(float dt)
{
    glm::vec3 distance{};
    if(Input::IsKeyPressed(SDL_SCANCODE_A))
    {
        distance = -22.0f * kWorldRight * dt;
    }
    if(Input::IsKeyPressed(SDL_SCANCODE_D))
    {
        distance = 22.0f * kWorldRight * dt;
    }
    Move(distance);

    if(Input::IsKeyPressed(SDL_SCANCODE_W))
    {
        if(m_CurrentShootDelay <= 0.0f)
        {
            // PIF PAF HERE

            m_CurrentShootDelay += m_ShootDelay;
        }
    }
}

void Cannon::Render(const Program& program) const
{
    program.SetUniform("uWorld", m_Transform);
    m_Mesh.Prepare();
    m_Mesh.Render(0);
}

void Cannon::SetPosition(const glm::vec3& position)
{
    m_Transform[3].x = position.x;
    m_Transform[3].y = position.y;
    m_Transform[3].z = position.z;
}

void Cannon::Move(const glm::vec3& distance)
{
    m_Transform[3].x += distance.x;
    m_Transform[3].y += distance.y;
    m_Transform[3].z += distance.z;
}