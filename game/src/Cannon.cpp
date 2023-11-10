#include "Cannon.hpp"

#include "Game.hpp"
#include "Tags.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"



Cannon::Cannon(Game& game)
:   Actor(game),
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Position = glm::vec3(0, 0, -15);
    m_Mesh = game.GetRenderSystem()->GetMesh("cannon");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("cannon_bitmap");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetTag(kInvader);
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