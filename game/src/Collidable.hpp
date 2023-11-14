#pragma once

#include "Tag.hpp"



class Actor;

struct CollisionInfo
{
    Actor* m_Target;
};

class Collidable
{
public:
    virtual ~Collidable() = default;

    virtual void OnCollisionEnter(const CollisionInfo& info) {}
};