#include "Box.hpp"

#include "Utils.hpp"



void Box::CreateFromBitmap(const Bitmap3D& bitmap)
{
    Utils::BoundingBoxFromBitmap(bitmap, *this);
}

void Box::Shrink(const glm::vec3& value)
{
    const glm::vec3 half_value = value/2.0f;

    m_Min += half_value;
    m_Max -= half_value;
}