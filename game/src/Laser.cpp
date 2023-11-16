#include "Laser.hpp"

#include "Game.hpp"
#include "Tag.hpp"
#include "Utils.hpp"

#include "glm/ext/matrix_transform.hpp"



Laser::Laser(Game& game, const glm::vec3& position, const glm::vec3& velocity, uint8_t collision_layer, uint8_t collision_mask)
:   Actor(game),
    m_ExistenceTimer(15.0f),
    m_Position(position),
    m_Velocity(velocity),
    m_Physics(*game.GetPhysicsSystem(), *this)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("laser");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");

    const Bitmap3D* bitmap = game.GetRenderSystem()->GetBitmap("laser");
    Box bounding_box;
    Utils::BoundingBoxFromBitmap(*bitmap, bounding_box);
    m_Physics.SetBoundingBox(bounding_box);
    m_Physics.SetPositionReference(m_Position);
    m_Physics.SetLayer(collision_layer);
    m_Physics.SetMask(collision_mask);
}

void Laser::Update(float dt)
{
    m_Position += m_Velocity * dt;

    m_ExistenceTimer -= dt;
    if(m_ExistenceTimer <= 0.0f)
    {
        Die();
    }
}

void Laser::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, m_Position);
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}

void Laser::OnCollisionEnter(const CollisionInfo& info)
{
    Die();
}

void Laser::Die()
{
    m_Game.RemoveActor(this);
}