#include "Cannon.hpp"

#include "Game.hpp"

#include "glm/ext/matrix_transform.hpp"



Cannon::Cannon(Game& game)
:   Actor(game)
{
    m_Mesh = game.GetRenderSystem()->GetMesh("cannon");
    m_Program = game.GetRenderSystem()->GetProgram("mesh");
}

void Cannon::Update(float dt)
{
    
}

void Cannon::Render() const
{
    m_Program->Use();
    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, glm::vec3(0, 0, -30));
    m_Program->SetUniform("uWorld", world);

    m_Mesh->Prepare();
    m_Mesh->Render(0);
}