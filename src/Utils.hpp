#pragma once

#include "Bitmap3D.hpp"

#include "glm/vec3.hpp"



namespace Utils
{
    void Load(const char* file_path, std::string& target);
    void BitmapFrameToVertices(const Bitmap3D& bitmap, uint32_t frame, uint32_t& offset, glm::vec3* vertices);
}