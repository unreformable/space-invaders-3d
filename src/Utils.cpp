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

    void BitmapFrameToVertices(const Bitmap3D& bitmap, uint32_t frame, uint32_t& offset, Vertex* vertices)
    {
        const uint32_t pixel_count = bitmap.Width() * bitmap.Height();
        const uint32_t pixel_offset = frame * pixel_count;

        for(uint32_t i = 0; i < pixel_count; i++)
        {
            const uint32_t y = i / bitmap.Width();
            const uint32_t x = i % bitmap.Width();

            if(bitmap.Data()[i + pixel_offset] == '0')
                continue;
            
            // Front
            vertices[offset + 0] = Vertex{ glm::vec3(x,     y,     0), glm::vec3(0, 0, 1) };
            vertices[offset + 1] = Vertex{ glm::vec3(x + 1, y,     0), glm::vec3(0, 0, 1) };
            vertices[offset + 2] = Vertex{ glm::vec3(x + 1, y + 1, 0), glm::vec3(0, 0, 1) };
            vertices[offset + 3] = Vertex{ glm::vec3(x + 1, y + 1, 0), glm::vec3(0, 0, 1) };
            vertices[offset + 4] = Vertex{ glm::vec3(x,     y + 1, 0), glm::vec3(0, 0, 1) };
            vertices[offset + 5] = Vertex{ glm::vec3(x,     y,     0), glm::vec3(0, 0, 1) };
            offset += 6;

            // Back
            vertices[offset + 0] = Vertex{ glm::vec3(x + 1, y,     -1), glm::vec3(0, 0, -1) };
            vertices[offset + 1] = Vertex{ glm::vec3(x,     y,     -1), glm::vec3(0, 0, -1) };
            vertices[offset + 2] = Vertex{ glm::vec3(x,     y + 1, -1), glm::vec3(0, 0, -1) };
            vertices[offset + 3] = Vertex{ glm::vec3(x,     y + 1, -1), glm::vec3(0, 0, -1) };
            vertices[offset + 4] = Vertex{ glm::vec3(x + 1, y + 1, -1), glm::vec3(0, 0, -1) };
            vertices[offset + 5] = Vertex{ glm::vec3(x + 1, y,     -1), glm::vec3(0, 0, -1) };
            offset += 6;

            // Left
            if(x == 0 || bitmap.Data()[y*bitmap.Width() + x - 1] == '0')
            {
                vertices[offset + 0] = Vertex{ glm::vec3(x, y,     -1), glm::vec3(-1, 0, 0) };
                vertices[offset + 1] = Vertex{ glm::vec3(x, y,      0), glm::vec3(-1, 0, 0) };
                vertices[offset + 2] = Vertex{ glm::vec3(x, y + 1,  0), glm::vec3(-1, 0, 0) };
                vertices[offset + 3] = Vertex{ glm::vec3(x, y + 1,  0), glm::vec3(-1, 0, 0) };
                vertices[offset + 4] = Vertex{ glm::vec3(x, y + 1, -1), glm::vec3(-1, 0, 0) };
                vertices[offset + 5] = Vertex{ glm::vec3(x, y,     -1), glm::vec3(-1, 0, 0) };
                offset += 6;
            }

            // Right
            if(x == bitmap.Width()-1 || bitmap.Data()[y*bitmap.Width() + x + 1] == '0')
            {
                vertices[offset + 0] = Vertex{ glm::vec3(x + 1, y,      0), glm::vec3(1, 0, 0) };
                vertices[offset + 1] = Vertex{ glm::vec3(x + 1, y,     -1), glm::vec3(1, 0, 0) };
                vertices[offset + 2] = Vertex{ glm::vec3(x + 1, y + 1, -1), glm::vec3(1, 0, 0) };
                vertices[offset + 3] = Vertex{ glm::vec3(x + 1, y + 1, -1), glm::vec3(1, 0, 0) };
                vertices[offset + 4] = Vertex{ glm::vec3(x + 1, y + 1,  0), glm::vec3(1, 0, 0) };
                vertices[offset + 5] = Vertex{ glm::vec3(x + 1, y,      0), glm::vec3(1, 0, 0) };
                offset += 6;
            }

            // Top
            if(y == bitmap.Height()-1 || bitmap.Data()[(y+1)*bitmap.Width() + x] == '0')
            {
                vertices[offset + 0] = Vertex{ glm::vec3(x,     y + 1,  0), glm::vec3(0, 1, 0) };
                vertices[offset + 1] = Vertex{ glm::vec3(x + 1, y + 1,  0), glm::vec3(0, 1, 0) };
                vertices[offset + 2] = Vertex{ glm::vec3(x + 1, y + 1, -1), glm::vec3(0, 1, 0) };
                vertices[offset + 3] = Vertex{ glm::vec3(x + 1, y + 1, -1), glm::vec3(0, 1, 0) };
                vertices[offset + 4] = Vertex{ glm::vec3(x,     y + 1, -1), glm::vec3(0, 1, 0) };
                vertices[offset + 5] = Vertex{ glm::vec3(x,     y + 1,  0), glm::vec3(0, 1, 0) };
                offset += 6;
            }

            // Bottom
            if(y == 0 || bitmap.Data()[(y-1)*bitmap.Width() + x] == '0')
            {
                vertices[offset + 0] = Vertex{ glm::vec3(x + 1, y,  0), glm::vec3(0, -1, 0) };
                vertices[offset + 1] = Vertex{ glm::vec3(x,     y,  0), glm::vec3(0, -1, 0) };
                vertices[offset + 2] = Vertex{ glm::vec3(x,     y, -1), glm::vec3(0, -1, 0) };
                vertices[offset + 3] = Vertex{ glm::vec3(x,     y, -1), glm::vec3(0, -1, 0) };
                vertices[offset + 4] = Vertex{ glm::vec3(x + 1, y, -1), glm::vec3(0, -1, 0) };
                vertices[offset + 5] = Vertex{ glm::vec3(x + 1, y,  0), glm::vec3(0, -1, 0) };
                offset += 6;
            }
        }
    }
}