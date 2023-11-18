#include "UfoSpawner.hpp"

#include "Event.hpp"
#include "Game.hpp"
#include "Ufo.hpp"
#include "RNG.hpp"



UfoSpawner::UfoSpawner(Game& game, const glm::vec3& ufo_position, const glm::vec3& ufo_velocity, float ufo_target_position_x)
:   Actor(game),
    m_UfoPosition(ufo_position),
    m_UfoVelocity(ufo_velocity),
    m_UfoTargetPositionX(ufo_target_position_x),
    m_CurrentSpawnChance(0.0f),
    m_SpawnChanceIncreasePerSec(2.0f),
    m_UfoAlive(false)
{
}

void UfoSpawner::Update(float dt)
{
    if(m_UfoAlive == false)
    {
        m_CurrentSpawnChance += m_SpawnChanceIncreasePerSec * dt;
        if(m_CurrentSpawnChance > 15.0f)
        {
            if(RNG::IntInRange(0, 100) == 100)
            {
                SpawnUfo();
                m_CurrentSpawnChance = 0.0f;
            }
        }
    }
}

void UfoSpawner::OnEvent(const Event& event)
{
    if(event.m_Type == EventType::UfoDied)
    {
        m_UfoAlive = false;
    }
}

void UfoSpawner::SpawnUfo()
{
    m_Game.AddActor(new Ufo(m_Game, m_UfoPosition, m_UfoVelocity, m_UfoTargetPositionX));
    m_UfoAlive = true;
}