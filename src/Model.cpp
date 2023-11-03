#include "Model.hpp"

#include "Utils.hpp"



Model::Model()
:   m_Frames{},
    m_Vao{},
    m_Vbo{}
{   
}

Model::~Model()
{
    glDeleteVertexArrays(1, &m_Vao);
    glDeleteBuffers(1, &m_Vbo);
}

void Model::CreateFromBitmap(const Bitmap3D& bitmap)
{
    this->~Model();

    m_VerticesCounts.resize(bitmap.Frames());
    m_VerticesOffsets.resize(bitmap.Frames());

    const uint32_t possible_vert_count = bitmap.PixelCount() * 6 * 2 * 3;
    glm::vec3 possible_vert[possible_vert_count];
    uint32_t offset = 0;
    for(uint32_t i = 0; i < bitmap.Frames(); i++)
    {
        m_VerticesOffsets[i] = offset;
        Utils::BitmapFrameToVertices(bitmap, i, offset, possible_vert);
        m_VerticesCounts[i] = offset - m_VerticesOffsets[i];
    }

    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(possible_vert), possible_vert, 0);
    m_Vbo = vbo;

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3*sizeof(GLfloat));
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glEnableVertexArrayAttrib(vao, 0);
    m_Vao = vao;
}

void Model::Render(uint32_t frame)
{
    glBindVertexArray(m_Vao);
    glDrawArrays(GL_TRIANGLES, m_VerticesOffsets[frame], m_VerticesCounts[frame]);
}