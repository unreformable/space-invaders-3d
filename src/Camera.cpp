#include "Camera.hpp"

#include "CoordinateSystem.hpp"



void Camera::LookAt(const glm::vec3& target_position)
{
    const glm::vec3 look_dir = glm::normalize(target_position - m_Position);
    m_Orientation = glm::quatLookAtRH(look_dir, kWorldUp);
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
}

glm::mat4 Camera::View() const
{
    const glm::vec3 pos_in_front = m_Position + m_Orientation * glm::vec3(0, 0, -1);
    return glm::lookAtRH(m_Position, pos_in_front, kWorldUp);
}