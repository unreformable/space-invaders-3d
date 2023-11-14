#include "RNG.hpp"

#include <random>


namespace RNG
{
    static std::random_device rd;
    static std::mt19937 e(rd());

    float FloatInRange(float min, float max)
    {
        std::uniform_real_distribution<> dist(min, max);

        return dist(e);
    }

    int IntInRange(int min, int max)
    {
        std::uniform_int_distribution<> dist(min, max);

        return dist(e);
    }
}