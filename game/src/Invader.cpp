#include "Invader.hpp"

#include "Game.hpp"
#include "Laser.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Invader::Invader(Game& game, const glm::vec3& position, const glm::vec3& velocity)
:   Actor(game),
    m_Position(position),
    m_Velocity(velocity),
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("small_invader");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("small_invader");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetTag(Tag::Invader);
}

void Invader::Update(float dt)
{
    m_Position += m_Velocity * dt;

    if(m_Position.x >= 90.0f)
    {
        m_Game.InvokeEvent(Event::InvaderReachedRightSide);
    }
    else if(m_Position.x <= -90.0f)
    {
        m_Game.InvokeEvent(Event::InvaderReachedLeftSide);
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

void Invader::OnEvent(const Event& event)
{
    if(event == Event::InvaderReachedLeftSide)
    {
        m_Velocity = glm::abs(m_Velocity);
    }
    else if(event == Event::InvaderReachedRightSide)
    {
        m_Velocity = glm::abs(m_Velocity) * -1.0f;
    }
}