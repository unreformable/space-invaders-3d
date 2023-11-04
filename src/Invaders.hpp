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

private:
    Invaders(const Invaders& other);
    Invaders& operator=(const Invaders& other);
    Invaders(Invaders&& other);
    Invaders& operator=(Invaders&& other);

private:
    Model m_SmallInvader;
    glm::ivec2 m_InvaderCount;
    std::vector<glm::mat4> m_InvaderTransforms;
};