#include "Lasers.hpp"



void Lasers::Create(const glm::mat4& transform, const glm::vec3& velocity, const Mesh* mesh)
{
    uint32_t i = 0;
    for(i = 0; i < m_Meshes.size(); i++)
    {
        if(m_Meshes[i] == mesh)
            break;
    }

    if(i == m_Meshes.size())
        m_Meshes.push_back(mesh);
    
    m_Transforms[i].push_back(transform);
    m_Velocities[i].push_back(velocity);
}

void Lasers::Update(float dt)
{
    // Move lasers
    for(uint32_t i = 0; i < m_Meshes.size(); i++)
    {
        std::vector<glm::mat4>& transforms = m_Transforms[i];
        std::vector<glm::vec3>& velocities = m_Velocities[i];

        for(uint32_t j = 0; j < transforms.size(); j++)
        {
            glm::mat4& transform = transforms[j];
            glm::vec3& velocity = velocities[j];

            glm::vec4& position_col = transform[3];

            position_col.x += velocity.x * dt;
            position_col.y += velocity.y * dt;
            position_col.z += velocity.z * dt;
        }
    }

    // Kill lasers out of limiting range
    for(uint32_t i = 0; i < m_Meshes.size(); i++)
    {
        std::vector<glm::mat4>& transforms = m_Transforms[i];
        
        for(uint32_t j = 0; j < transforms.size(); j++)
        {
            glm::mat4& transform = transforms[j];

            const glm::vec3 position = glm::vec3(
                transform[3].x,
                transform[3].y,
                transform[3].z
            );

            if(position.x < m_Limit.Min().x || position.x > m_Limit.Max().x
            || position.y < m_Limit.Min().y || position.y > m_Limit.Max().y
            || position.z < m_Limit.Min().z || position.z > m_Limit.Max().z)
            {
                transform = transforms.back();
                transforms.pop_back();

                m_Velocities[i][j] = m_Velocities[i].back();
                m_Velocities[i].pop_back();

                if(transforms.empty() == true)
                {
                    m_Transforms.erase(i);
                    m_Velocities.erase(i);
                }
            }
        }
    }
}

void Lasers::Render(const Program& program)
{
    for(uint32_t i = 0; i < m_Meshes.size(); i++)
    {
        const Mesh* mesh = m_Meshes[i];
        const std::vector<glm::mat4>& transforms = m_Transforms[i];

        mesh->Prepare();

        for(const glm::mat4& transform : transforms)
        {
            program.SetUniform("uWorld", transform);
            mesh->Render(0);
        }
    }
}