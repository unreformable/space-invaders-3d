#pragma once

#include "Model.hpp"
#include "Program.hpp"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"



class Invaders
{
public:
    Invaders();

    void Move(const glm::vec3& distance);
    void Render(const Program& program) const;
    // FloatRect GetBoundingRect() const;

    inline uint32_t Rows() const { return m_Rows; }
    inline uint32_t Cols() const { return m_Cols; }

private:
    Invaders(const Invaders& other);
    Invaders& operator=(const Invaders& other);
    Invaders(Invaders&& other);
    Invaders& operator=(Invaders&& other);

private:
    Model m_SmallInvader;
    uint32_t m_Rows;
    uint32_t m_Cols;
    std::vector<glm::mat4> m_InvaderTransforms;
};