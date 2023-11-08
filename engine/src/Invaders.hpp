#pragma once

#include "Mesh.hpp"
#include "Program.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"



class Invaders
{
public:
    Invaders(uint32_t rows, uint32_t cols);

    void Update(float dt);
    void Render(const Program& program) const;
    
    glm::vec3 Position() const;
    inline const Box& BoundingBox() const { return m_BoundingBox; }

    inline uint32_t Rows() const { return m_Rows; }
    inline uint32_t Cols() const { return m_Cols; }

private:
    Invaders(const Invaders& other);
    Invaders& operator=(const Invaders& other);
    Invaders(Invaders&& other);
    Invaders& operator=(Invaders&& other);

private:
    std::vector<glm::mat4> m_InvaderTransforms;
    const uint32_t m_Rows;
    const uint32_t m_Cols;

    Mesh m_SmallInvader;

    const float m_MoveDelay;
    float m_CurrentMoveDelay;

    Box m_BoundingBox;
};