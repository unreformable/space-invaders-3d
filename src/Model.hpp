#pragma once

#include "Bitmap3D.hpp"

#include "glad/glad.h"

#include <stdint.h>
#include <vector>



class Model
{
public:
    Model();
    ~Model();

    void CreateFromBitmap(const Bitmap3D& bitmap);
    void Render(uint32_t frame);
    
    inline uint32_t Frames() const { return m_Frames; }

private:
    Model(const Model& other);
    Model& operator=(const Model& other);
    Model(Model&& other);
    Model& operator=(Model&& other);

private:
    uint32_t m_Frames;
    GLuint m_Vao;
    GLuint m_Vbo;
    std::vector<uint32_t> m_VerticesCounts;
    std::vector<uint32_t> m_VerticesOffsets;
};