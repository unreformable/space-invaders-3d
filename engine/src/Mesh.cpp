#include "Mesh.hpp"

#include "Utils.hpp"



Mesh::Mesh()
:   m_Frames{},
    m_Vao{},
    m_Vbo{}
{
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
}

void Mesh::CreateFromBitmap(const Bitmap3D& bitmap)
{
    this->~Mesh();

    m_VertexCounts.resize(bitmap.Frames());
    m_VertexOffsets.resize(bitmap.Frames());

    // Each pixel has possible 6 faces, each face has 2 triangles,
    // each triangle has 3 vertices, each vertex is position + normal
    const uint32_t possible_vert_count = bitmap.PixelCount() * 6 * 2 * 3;
    Vertex possible_vert[possible_vert_count];
    uint32_t offset = 0;
    for(uint32_t i = 0; i < bitmap.Frames(); i++)
    {
        m_VertexOffsets[i] = offset;
        Utils::VerticesFromBitmapFrame(bitmap, i, offset, possible_vert);
        m_VertexCounts[i] = offset - m_VertexOffsets[i];
    }

    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(possible_vert), possible_vert, 0);
    m_Vbo = vbo;

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6*sizeof(GLfloat));
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat));
    glVertexArrayAttribBinding(vao, 1, 0);
    glEnableVertexArrayAttrib(vao, 1);
    m_Vao = vao;
}

void Mesh::Prepare() const
{
    glBindVertexArray(m_Vao);
}

void Mesh::Render(uint32_t frame) const
{
    glDrawArrays(GL_TRIANGLES, m_VertexOffsets[frame], m_VertexCounts[frame]);
}