#include "Invader.hpp"

#include "Game.hpp"
#include "InvadersManager.hpp"
#include "Laser.hpp"
#include "RNG.hpp"
#include "Tag.hpp"
#include "Utils.hpp"


#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Invader::Invader(Game& game, const glm::vec3& position)
:   Actor(game),
    m_Position(position),
    m_Velocity{},
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("small_invader");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("small_invader");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetMask(kTagCannonLaser);
    m_Physics.SetLayer(kTagInvader);

    m_CurrentShootTimer = RNG::FloatInRange(2.0f, 6.0f);
}

void Invader::Update(float dt)
{
    m_Position += m_Velocity * dt;

    m_CurrentShootTimer -= dt;
    if(m_CurrentShootTimer <= 0.0f)
    {
        if(RNG::IntInRange(0, 10) > 7)
            Shoot();
        
        m_CurrentShootTimer = RNG::FloatInRange(2.0f, 6.0f);
    }

    if(m_Position.x <= InvadersManager::MIN_X)
    {
        Event event;
        event.m_Type = EventType::InvaderReachedLeftSide;
        m_Game.InvokeEvent(event);
    }
    else if(m_Position.x >= InvadersManager::MAX_X)
    {
        Event event;
        event.m_Type = EventType::InvaderReachedRightSide;
        m_Game.InvokeEvent(event);
    }
}

void Invader::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, m_Position);
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}

void Invader::OnCollisionEnter(const CollisionInfo& info)
{
    m_Game.RemoveActor(this);
}

void Invader::OnEvent(const Event& event)
{
    if(event.m_Type == EventType::InvadersChangeVelocity)
    {
        m_Velocity = event.m_Data.m_Velocity;
    }
}

void Invader::Shoot()
{
    m_Game.AddActor(new Laser(m_Game, m_Position + glm::vec3(0, 0, 5.6f), {0, 0, 25}, kTagInvaderLaser, kTagCannon | kTagWall | kTagCannonLaser));
}