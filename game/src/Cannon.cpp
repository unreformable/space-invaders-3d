#include "Cannon.hpp"

#include "Game.hpp"
#include "Laser.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Cannon::Cannon(Game& game, const glm::vec3& position)
:   Actor(game),
    m_Position(position),
    m_Physics(*game.GetPhysicsSystem(), *this),
    m_ShootCooldown(1.0f),
    m_CurrentShootCooldown{}
{
    m_Mesh = game.GetRenderSystem()->GetMesh("cannon");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("cannon");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetMask(kTagInvaderLaser);
}

void Cannon::Update(float dt)
{
    if(m_Game.GetInput()->IsKeyPressed(SDL_SCANCODE_A))
    {
        m_Position.x -= 10.0f * dt;
    }
    if(m_Game.GetInput()->IsKeyPressed(SDL_SCANCODE_D))
    {
        m_Position.x += 10.0f * dt;
    }
    if(m_Game.GetInput()->IsKeyPressed(SDL_SCANCODE_W))
    {
        if(m_CurrentShootCooldown <= 0.0f)
        {
            m_Game.AddActor(new Laser(m_Game, m_Position + glm::vec3(0, 0, -5.6f), {0, 0, -25}, kTagCannonLaser));

            m_CurrentShootCooldown = m_ShootCooldown;
        }
    }

    m_CurrentShootCooldown -= dt;
}

void Cannon::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, m_Position);
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}

void Cannon::OnCollisionEnter(const CollisionInfo& info)
{
    std::cerr << "Ouch!";
}