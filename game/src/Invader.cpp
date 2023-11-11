#include "Invader.hpp"

#include "Game.hpp"
#include "Laser.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Invader::Invader(Game& game, const glm::vec3& position)
:   Actor(game),
    m_Position(position),
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("small_invader");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("small_invader");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetTag(kInvader);
}

void Invader::Update(float dt)
{
    m_Position += glm::vec3(5, 0, 0) * dt;
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