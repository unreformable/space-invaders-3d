#pragma once

#include "Box.hpp"
#include "Tag.hpp"



class Actor;

struct CollisionInfo
{
    Actor* m_Target;
    glm::vec3 m_TargetPosition;
    Box m_TargetBoundingBox;
};

class Collidable
{
public:
    virtual ~Collidable() = default;

    virtual void OnCollisionEnter(const CollisionInfo& info) {}
};