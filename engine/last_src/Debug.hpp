#pragma once

#include "Box.hpp"

#include <iostream>



std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
{
    return os << vec3.x << ' ' << vec3.y << ' ' << vec3.z;
}

std::ostream& operator<<(std::ostream& os, const Box& box)
{
    os << "Min: " << box.Min() << '\n';
    os << "Max: " << box.Max();

    return os;
}