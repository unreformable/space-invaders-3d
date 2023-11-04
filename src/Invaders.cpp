#include "Invaders.hpp"

#include "glm/ext/matrix_transform.hpp"



Invaders::Invaders()
{
    Bitmap3D bitmap;
    bitmap.Load("../assets/bitmaps/small_invader");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();
    m_SmallInvader.CreateFromBitmap(bitmap);

    m_InvaderCount.x = 11;
    m_InvaderCount.y = 5;

    const uint32_t invader_count = m_InvaderCount.x * m_InvaderCount.y;
    m_InvaderTransforms.reserve(invader_count);
    for(uint32_t i = 0; i < invader_count; i++)
    {
        const uint32_t x = i % m_InvaderCount.x;
        const uint32_t y = i / m_InvaderCount.x;

        const glm::vec3 distance = 13.0f * glm::vec3(x, y, 0);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, distance);
        m_InvaderTransforms.emplace_back(std::move(transform));
    }
}

void Invaders::Move(const glm::vec3& distance)
{

}

void Invaders::Render(const Program& program) const
{
    m_SmallInvader.Prepare();
    for(const glm::mat4& transform : m_InvaderTransforms)
    {
        program.SetUniform("uWorld", transform);
        m_SmallInvader.Render(0);
    }
}