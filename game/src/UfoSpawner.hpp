#pragma once

#include "Actor.hpp"



class UfoSpawner: public Actor
{
public:
    UfoSpawner(Game& game, const glm::vec3& ufo_position, const glm::vec3& ufo_velocity, float ufo_target_position_x);

    virtual void Update(float dt);
    virtual void OnEvent(const Event& event);

private:
    void SpawnUfo();

private:
    glm::vec3 m_UfoPosition;
    glm::vec3 m_UfoVelocity;
    float m_UfoTargetPositionX;
    float m_CurrentSpawnChance;
    float m_SpawnChanceIncreasePerSec;
    bool m_UfoAlive;
};