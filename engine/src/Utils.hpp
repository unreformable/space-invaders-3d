#pragma once

#include "Bitmap3D.hpp"
#include "Box.hpp"
#include "Vertex.hpp"



namespace Utils
{
    void Load(const char* file_path, std::string& target);
    void VerticesFromBitmapFrame(const Bitmap3D& bitmap, uint32_t frame, uint32_t& vertex_count, Vertex* vertices);
    void BoundingBoxFromBitmap(const Bitmap3D& bitmap, Box& box);
    bool Collides(const glm::vec3& pos1, const Box& box1, const glm::vec3& pos2, const Box& box2);
}