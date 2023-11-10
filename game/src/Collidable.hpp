#pragma once

#include <stdint.h>



class Actor;

struct CollisionInfo
{
    Actor* m_Target;
    uint32_t m_Tag;
};

class Collidable
{
public:
    virtual ~Collidable() = default;

    virtual void OnCollisionEnter(const CollisionInfo& info) {}
};