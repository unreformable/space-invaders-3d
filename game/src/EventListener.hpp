#pragma once

#include "Event.hpp"



class EventListener
{
public:
    virtual ~EventListener() = default;

    virtual void OnEvent(const Event& event) {}
};