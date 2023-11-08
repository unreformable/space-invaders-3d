#pragma once

#include "glm/gtc/quaternion.hpp"
#include "glm/mat4x4.hpp"



class Camera
{
public:
    void LookAt(const glm::vec3& target_position);
    void SetPosition(const glm::vec3& position);

    glm::mat4 View() const;

private:
    glm::vec3 m_Position;
    glm::quat m_Orientation;
};