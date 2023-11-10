#include "Utils.hpp"

#include <fstream>
#include <iostream>



namespace Utils
{
    void Load(const char* file_path, std::string& target)
    {
        std::ifstream file(file_path, std::ios::in | std::ios::binary);

        if(file.is_open() == false)
        {
            std::cerr << "Could not open file from given path: " << file_path << std::endl;
            return;
        }

        file.seekg(0, std::ios::end);
        target.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&target[0], target.size());
        file.close();
    }

    // Do not touch!
    void VerticesFromBitmapFrame(const Bitmap3D& bitmap, uint32_t frame, uint32_t& vertex_count, Vertex* vertices)
    {
        const uint32_t pixel_count = bitmap.Width() * bitmap.Height();
        const uint32_t pixel_offset = frame * pixel_count;

        const glm::vec3 to_center_adjust = glm::vec3(
            -static_cast<float>(bitmap.Width()) / 2.0f,
            -0.5f,
             static_cast<float>(bitmap.Height()) / 2.0f
        );

        const glm::vec3 left_bottom_front  = glm::vec3(0, 0,  0);
        const glm::vec3 right_bottom_front = glm::vec3(1, 0,  0);
        const glm::vec3 left_top_front     = glm::vec3(0, 1,  0);
        const glm::vec3 right_top_front    = glm::vec3(1, 1,  0);
        const glm::vec3 left_bottom_back   = glm::vec3(0, 0, -1);
        const glm::vec3 right_bottom_back  = glm::vec3(1, 0, -1);
        const glm::vec3 left_top_back      = glm::vec3(0, 1, -1);
        const glm::vec3 right_top_back     = glm::vec3(1, 1, -1);

        for(uint32_t i = 0; i < pixel_count; i++)
        {
            const int x = i % bitmap.Width();
            const int y = i / bitmap.Width();

            const glm::vec3 offset = glm::vec3(x, 0, -y) + to_center_adjust;

            if(bitmap.Data()[i + pixel_offset] == '0')
                continue;
            
            // Front
            if(y == 0 || bitmap.Data()[(y-1)*bitmap.Width() + x] == '0')
            {
                vertices[vertex_count + 0] = Vertex{ left_bottom_front  + offset, glm::vec3(0, 0, 1) };
                vertices[vertex_count + 1] = Vertex{ right_bottom_front + offset, glm::vec3(0, 0, 1) };
                vertices[vertex_count + 2] = Vertex{ right_top_front    + offset, glm::vec3(0, 0, 1) };
                vertices[vertex_count + 3] = Vertex{ right_top_front    + offset, glm::vec3(0, 0, 1) };
                vertices[vertex_count + 4] = Vertex{ left_top_front     + offset, glm::vec3(0, 0, 1) };
                vertices[vertex_count + 5] = Vertex{ left_bottom_front  + offset, glm::vec3(0, 0, 1) };
                vertex_count += 6;
            }

            // Back
            if(y == bitmap.Height()-1 || bitmap.Data()[(y+1)*bitmap.Width() + x] == '0')
            {
                vertices[vertex_count + 0] = Vertex{ right_bottom_back + offset, glm::vec3(0, 0, -1) };
                vertices[vertex_count + 1] = Vertex{ left_bottom_back  + offset, glm::vec3(0, 0, -1) };
                vertices[vertex_count + 2] = Vertex{ left_top_back     + offset, glm::vec3(0, 0, -1) };
                vertices[vertex_count + 3] = Vertex{ left_top_back     + offset, glm::vec3(0, 0, -1) };
                vertices[vertex_count + 4] = Vertex{ right_top_back    + offset, glm::vec3(0, 0, -1) };
                vertices[vertex_count + 5] = Vertex{ right_bottom_back + offset, glm::vec3(0, 0, -1) };
                vertex_count += 6;
            }

            // Left
            if(x == 0 || bitmap.Data()[y*bitmap.Width() + x - 1] == '0')
            {
                vertices[vertex_count + 0] = Vertex{ left_bottom_back  + offset, glm::vec3(-1, 0, 0) };
                vertices[vertex_count + 1] = Vertex{ left_bottom_front + offset, glm::vec3(-1, 0, 0) };
                vertices[vertex_count + 2] = Vertex{ left_top_front    + offset, glm::vec3(-1, 0, 0) };
                vertices[vertex_count + 3] = Vertex{ left_top_front    + offset, glm::vec3(-1, 0, 0) };
                vertices[vertex_count + 4] = Vertex{ left_top_back     + offset, glm::vec3(-1, 0, 0) };
                vertices[vertex_count + 5] = Vertex{ left_bottom_back  + offset, glm::vec3(-1, 0, 0) };
                vertex_count += 6;
            }

            // Right
            if(x == bitmap.Width()-1 || bitmap.Data()[y*bitmap.Width() + x + 1] == '0')
            {
                vertices[vertex_count + 0] = Vertex{ right_bottom_front + offset, glm::vec3(1, 0, 0) };
                vertices[vertex_count + 1] = Vertex{ right_bottom_back  + offset, glm::vec3(1, 0, 0) };
                vertices[vertex_count + 2] = Vertex{ right_top_back     + offset, glm::vec3(1, 0, 0) };
                vertices[vertex_count + 3] = Vertex{ right_top_back     + offset, glm::vec3(1, 0, 0) };
                vertices[vertex_count + 4] = Vertex{ right_top_front    + offset, glm::vec3(1, 0, 0) };
                vertices[vertex_count + 5] = Vertex{ right_bottom_front + offset, glm::vec3(1, 0, 0) };
                vertex_count += 6;
            }

            // Top
            vertices[vertex_count + 0] = Vertex{ left_top_front  + offset, glm::vec3(0, 1, 0) };
            vertices[vertex_count + 1] = Vertex{ right_top_front + offset, glm::vec3(0, 1, 0) };
            vertices[vertex_count + 2] = Vertex{ right_top_back  + offset, glm::vec3(0, 1, 0) };
            vertices[vertex_count + 3] = Vertex{ right_top_back  + offset, glm::vec3(0, 1, 0) };
            vertices[vertex_count + 4] = Vertex{ left_top_back   + offset, glm::vec3(0, 1, 0) };
            vertices[vertex_count + 5] = Vertex{ left_top_front  + offset, glm::vec3(0, 1, 0) };
            vertex_count += 6;

            // Bottom
            vertices[vertex_count + 0] = Vertex{ right_bottom_front + offset, glm::vec3(0, -1, 0) };
            vertices[vertex_count + 1] = Vertex{ left_bottom_front  + offset, glm::vec3(0, -1, 0) };
            vertices[vertex_count + 2] = Vertex{ left_bottom_back   + offset, glm::vec3(0, -1, 0) };
            vertices[vertex_count + 3] = Vertex{ left_bottom_back   + offset, glm::vec3(0, -1, 0) };
            vertices[vertex_count + 4] = Vertex{ right_bottom_back  + offset, glm::vec3(0, -1, 0) };
            vertices[vertex_count + 5] = Vertex{ right_bottom_front + offset, glm::vec3(0, -1, 0) };
            vertex_count += 6;
        }
    }

    void BoundingBoxFromBitmap(const Bitmap3D& bitmap, Box& box)
    {
        box.SetMin({
            -static_cast<float>(bitmap.Width()) / 2.0f,
            -0.5f,
            -static_cast<float>(bitmap.Height()) / 2.0f
        });
        box.SetMax({
            static_cast<float>(bitmap.Width()) / 2.0f,
            0.5f,
            static_cast<float>(bitmap.Height()) / 2.0f
        });
    }

    bool Collides(const glm::vec3& pos1, const Box& box1, const glm::vec3& pos2, const Box& box2)
    {
        return !(
               pos1.x + box1.Min().x > pos2.x + box2.Max().x || pos1.x + box1.Max().x < pos2.x + box2.Min().x
            || pos1.y + box1.Min().y > pos2.y + box2.Max().y || pos1.y + box1.Max().y < pos2.y + box2.Min().y
            || pos1.z + box1.Min().z > pos2.z + box2.Max().z || pos1.z + box1.Max().z < pos2.z + box2.Min().z
        );
    }
}