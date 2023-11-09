#pragma once

#include "Bitmap3D.hpp"

#include "glm/vec3.hpp"



class Box
{
public:
    void CreateFromBitmap(const Bitmap3D& bitmap);

    inline void SetMin(const glm::vec3& min) { m_Min = min; }
    inline void SetMax(const glm::vec3& max) { m_Max = max; }

    inline const glm::vec3& Min() const { return m_Min; }
    inline const glm::vec3& Max() const { return m_Max; }

    inline glm::vec3 HalfSize() const { return (m_Max - m_Min) / 2.0f; }

private:
    Box(const Box& other);
    Box& operator=(const Box& other);
    Box(Box&& other);
    Box& operator=(Box&& other);

private:
    glm::vec3 m_Min;
    glm::vec3 m_Max;
};