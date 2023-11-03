#pragma once

#include "Bitmap3D.hpp"

#include "glm/vec3.hpp"



namespace Utils
{
    void BitmapFrameToVertices(const Bitmap3D& bitmap, const uint32_t frame, uint32_t& offset, glm::vec3* vertices);
}