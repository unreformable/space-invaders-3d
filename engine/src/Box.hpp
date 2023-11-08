#pragma once

#include "glm/vec3.hpp"



class Box
{
public:
    inline void SetMin(const glm::vec3& min) { m_Min = min; }
    inline void SetMax(const glm::vec3& max) { m_Max = max; }

    inline const glm::vec3& Min() const { return m_Min; }
    inline const glm::vec3& Max() const { return m_Max; }

    glm::vec3 HalfSize() const
    {
        return (m_Max - m_Min) / 2.0f;
    }

private:
    glm::vec3 m_Min;
    glm::vec3 m_Max;
};