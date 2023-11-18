#include "Ufo.hpp"

#include "Game.hpp"
#include "Laser.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Ufo::Ufo(Game& game, const glm::vec3& position, const glm::vec3& velocity, float target_position_x)
:   Actor(game),
    m_Position(position),
    m_Velocity(velocity),
    m_Physics(*game.GetPhysicsSystem(), *this),
    m_TargetPositionX(target_position_x)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("ufo");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    const Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("ufo");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetLayer(kTagUfo);
    m_Physics.SetMask(kTagInvaderLaser);
}

void Ufo::Update(float dt)
{
    m_Position += m_Velocity * dt;
    if(m_Position.x >= m_TargetPositionX)
    {
        m_Game.RemoveActor(this);
    }
}

void Ufo::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, m_Position);
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}

void Ufo::OnCollisionEnter(const CollisionInfo& info)
{
    Event event;
    event.m_Type = EventType::UfoDied;
    m_Game.InvokeEvent(event);

    m_Game.RemoveActor(this);
}