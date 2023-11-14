#pragma once

#include "Collidable.hpp"
#include "EventListener.hpp"

#include "SDL2/SDL_events.h"

#include <list>
#include <vector>



class Game;

class Actor: public Collidable, public EventListener
{
public:
    Actor(Game& game);
    virtual ~Actor();

    virtual void Update(float dt);
    virtual void Render() const;
    virtual void OnCollisionEnter(const CollisionInfo& info);
    virtual void OnEvent(const Event& event);

    void SetParent(Actor* parent);

    // !Only for internal use! These allow to properly add/remove children while in runtime
    void CheckAddActors();
    void CheckRemoveChildren();

private:
    void RemoveChildren();
    void RemoveChild(Actor* child);

protected:
    std::vector<Actor*> m_Children;
    Actor* m_Parent;
    Game& m_Game;

    std::list<Actor*> m_ActorsToAdd;
    std::list<Actor*> m_ChildrenToRemove;
};