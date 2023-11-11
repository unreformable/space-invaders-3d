#pragma once

#include "Tag.hpp"

#include <stdint.h>



class Actor;

struct CollisionInfo
{
    Actor* m_Target;
    Tag m_TargetTag;
};

class Collidable
{
public:
    virtual ~Collidable() = default;

    virtual void OnCollisionEnter(const CollisionInfo& info) {}
};