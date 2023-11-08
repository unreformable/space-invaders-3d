#include "Invaders.hpp"

#include "CoordinateSystem.hpp"

#include "glm/ext/matrix_transform.hpp"



Invaders::Invaders(uint32_t rows, uint32_t cols)
:   m_Rows(rows),
    m_Cols(cols),
    m_MoveDelay(1.0f),
    m_CurrentMoveDelay(m_MoveDelay)
{
    Bitmap3D bitmap;
    bitmap.Load("../../assets/bitmaps/small_invader");
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

    const glm::vec3 first_invader_pos = glm::vec3(m_InvaderTransforms.front()[3]);
    const glm::vec3 last_invader_pos = glm::vec3(m_InvaderTransforms.back()[3]);
    m_BoundingBox.SetMin(first_invader_pos - m_SmallInvader.BoundingBox().HalfSize());
    m_BoundingBox.SetMax(last_invader_pos + m_SmallInvader.BoundingBox().HalfSize());
}

void Invaders::Update(float dt)
{
    // const uint32_t first = row * m_Cols;
    // const uint32_t last = (row + 1) * m_Cols;

    // for(uint32_t i = first; i < last; i++)
    // {
    //     glm::mat4& transform = m_InvaderTransforms[i];
    //     transform = glm::translate(transform, distance);
    // }

    if(m_CurrentMoveDelay > m_MoveDelay)
    {
        for(glm::mat4& transform : m_InvaderTransforms)
        {
            transform = glm::translate(transform, glm::vec3(1.5f, 0, 0));
        }

        m_CurrentMoveDelay -= m_MoveDelay;
    }
    else
    {
        m_CurrentMoveDelay += dt;
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

glm::vec3 Invaders::Position() const
{
    return m_BoundingBox.Min() + m_SmallInvader.BoundingBox().HalfSize();
}