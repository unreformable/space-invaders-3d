#pragma once



class Game
{
public:
    Game();
    ~Game();
    void Run();

private:
    void HandleInput();
    void Update();
    void Render();

private:
    float m_DeltaTime;
    float m_LoopStartMs;

    bool m_Running;
};