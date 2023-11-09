#include "Actor.hpp"

#include "Mesh.hpp"
#include "Program.hpp"



class Cannon: public Actor
{
public:
    Cannon(Game& game);

    virtual void Update(float dt);
    virtual void Render() const;

private:
    Mesh* m_Mesh;
    Program* m_Program;
};