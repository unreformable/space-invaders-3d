#pragma once

#include "Bitmap3D.hpp"
#include "Box.hpp"

#include "glad/glad.h"

#include <stdint.h>
#include <vector>



class Mesh
{
public:
    Mesh();
    ~Mesh();

    void CreateFromBitmap(const Bitmap3D& bitmap);
    void Prepare() const;
    void Render(uint32_t frame) const;

    inline uint32_t Frames() const { return m_Frames; }

private:
    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(Mesh&& other);

private:
    GLuint m_Vao;
    GLuint m_Vbo;
    uint32_t m_Frames;
    std::vector<uint32_t> m_VertexCounts;
    std::vector<uint32_t> m_VertexOffsets;
};