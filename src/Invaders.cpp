#include "Invaders.hpp"

#include "CoordinateSystem.hpp"

#include "glm/ext/matrix_transform.hpp"



Invaders::Invaders()
:   m_Rows(5),
    m_Cols(11)
{
    Bitmap3D bitmap;
    bitmap.Load("../assets/bitmaps/small_invader");
    // Reverse bitmap, so bitmap's y goes with mesh's y
    bitmap.ReverseEachFrame();
    m_SmallInvader.CreateFromBitmap(bitmap);

    const uint32_t invader_count = m_Rows * m_Cols;
    m_InvaderTransforms.reserve(invader_count);
    for(uint32_t i = 0; i < invader_count; i++)
    {
        const float x = i % m_Cols;
        const float z = i / m_Cols;

        const glm::vec3 offset = 13.0f * glm::vec3(x, 0, -z);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, offset);
        m_InvaderTransforms.emplace_back(std::move(transform));
    }
}

void Invaders::Move(const glm::vec3& distance)
{
    // const uint32_t first = row * m_Cols;
    // const uint32_t last = (row + 1) * m_Cols;

    // for(uint32_t i = first; i < last; i++)
    // {
    //     glm::mat4& transform = m_InvaderTransforms[i];
    //     transform = glm::translate(transform, distance);
    // }

    for(glm::mat4& transform : m_InvaderTransforms)
    {
        transform = glm::translate(transform, distance);
    }
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