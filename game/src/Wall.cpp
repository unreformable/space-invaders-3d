#include "Wall.hpp"

#include "Game.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"

#include <iostream>



Wall::Wall(Game& game, const glm::vec3& position)
:   Actor(game),
    m_Position(position),
    m_Health(9),
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("wall");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    const Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("wall");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    bounding_box.Shrink({0, 0, 2});
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetLayer(kTagWall);
    m_Physics.SetMask(kTagCannonLaser | kTagInvaderLaser);
}

void Wall::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, m_Position);
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}

void Wall::OnCollisionEnter(const CollisionInfo& info)
{
    m_Health -= 1;
    if(m_Health <= 0)
    {
        m_Game.RemoveActor(this);
    }
}