#include "Actor.hpp"

#include "Mesh.hpp"
#include "PhysicsSystem.hpp"
#include "Program.hpp"



class Cannon: public Actor
{
public:
    Cannon(Game& game);

    virtual void Update(float dt);
    virtual void Render() const;

private:
    glm::vec3 m_Position;
    Mesh* m_Mesh;
    Program* m_Program;
    PhysicsComponent m_Physics;
};