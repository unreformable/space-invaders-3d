#pragma once

#include "glm/vec3.hpp"



/*
         Y
         |
         |
         |
         |
         |
         |____________ X
        /
       /
      /
     /
    Z
*/

inline constexpr const glm::vec3 kWorldUp{ 0, 1, 0 };
inline constexpr const glm::vec3 kWorldRight{ 1, 0, 0 };