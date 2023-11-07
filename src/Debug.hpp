#pragma once

#include "glm/vec3.hpp"

#include <iostream>



std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
{
    return os << vec3.x << ' ' << vec3.y << ' ' << vec3.z;
}