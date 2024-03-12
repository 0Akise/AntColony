#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

struct CellCoord
{
    int x;
    int y;

    bool operator==(const CellCoord &other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

namespace std
{
    template <>
    struct hash<CellCoord>
    {
        std::size_t operator()(const CellCoord &coord) const
        {
            return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y);
        }
    };
}

class MathUtil
{
public:
    static constexpr float PI = 3.141592;

    static float degtorad(float degrees)
    {
        return degrees * (PI / 180);
    }

    static float radtodeg(float radians)
    {
        return radians * (180 / PI);
    }

    static float lerpangle(float startAngle, float endAngle, float factor) {
        float difference = endAngle - startAngle;

        while (difference < -180) difference += 360;
        while (difference > 180) difference -= 360;

        return startAngle + difference * factor;
    }

    static float distance(float x1, float y1, float x2, float y2)
    {
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }

    static float distance(sf::Vector2f v1, sf::Vector2f v2)
    {
        return distance(v1.x, v1.y, v2.x, v2.y);
    }

    static float pointtowards(sf::Vector2f from, sf::Vector2f to)
    {
        return std::atan2(to.y - from.y, to.x - from.x);
    }

    static float random(float min, float max)
    {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }
};
