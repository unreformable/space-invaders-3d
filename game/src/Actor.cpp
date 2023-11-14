#include "Actor.hpp"

#include <algorithm>
#include <iostream>



Actor::Actor(Game& game)
:   m_Game(game),
    m_Parent{}
{
}

Actor::~Actor()
{
    RemoveChildren();
}

void Actor::Update(float dt)
{
    for(Actor* child : m_Children)
        child->Update(dt);
}

void Actor::Render() const
{
    for(Actor* child : m_Children)
        child->Render();
}

void Actor::OnCollisionEnter(const CollisionInfo& info)
{
    for(Actor* child : m_Children)
        child->OnCollisionEnter(info);
}

void Actor::OnEvent(const Event& event)
{
    for(Actor* child : m_Children)
        child->OnEvent(event);
}

void Actor::SetParent(Actor* parent)
{
    if(m_Parent != nullptr)
    {
        if(parent == m_Parent)
            return;
        
        m_Parent->m_ChildrenToRemove.push_back(this);
    }
    
    if(parent == nullptr)
    {
        RemoveChildren();
    }
    else
    {
        m_Parent = parent;
        m_Parent->m_ActorsToAdd.push_back(this);
    }
}

void Actor::CheckAddActors()
{
    for(Actor* new_actor : m_ActorsToAdd)
        m_Children.push_back(new_actor);
    m_ActorsToAdd.clear();

    for(Actor* child : m_Children)
        child->CheckAddActors();
}

void Actor::CheckRemoveChildren()
{
    for(Actor* child: m_ChildrenToRemove)
    {
        auto it = std::find(std::begin(m_Children), std::end(m_Children), child);
        assert(child != nullptr);
        assert(it != m_Children.end());
        m_Children.erase(it);
        delete child;
    }
    m_ChildrenToRemove.clear();

    for(Actor* child : m_Children)
        child->CheckRemoveChildren();
}

void Actor::RemoveChildren()
{
    for(Actor* child : m_Children)
    {
        child->RemoveChildren();
        m_ChildrenToRemove.push_back(child);
    }
}

void Actor::RemoveChild(Actor* child)
{
    auto it = std::find(std::begin(m_Children), std::end(m_Children), child);
    m_Children.erase(it);
}