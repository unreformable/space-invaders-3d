#pragma once

#include "Bitmap3D.hpp"
#include "Vertex.hpp"



namespace Utils
{
    void Load(const char* file_path, std::string& target);
    void VerticesFromBitmapFrame(const Bitmap3D& bitmap, uint32_t frame, uint32_t& vertex_count, Vertex* vertices);
}