#pragma once

#include <util.hpp>

namespace R_01
{
    enum class ObjectType
    {
        HIVE,
        ANT,
        FOOD,
        PHEROMONE,
        WALL,
    };

    struct CellCoord
    {
        int32_t x;
        int32_t y;

        bool operator==(const CellCoord &other) const
        {
            return (x == other.x) && (y == other.y);
        }
    };

    class IObject
    {
    public:
        virtual ~IObject() = default;
        virtual ObjectType getType() const = 0;
        virtual sf::Vector2f getPos() const = 0;
        virtual float_t getHitbox() const = 0;
        
        virtual void setPos(sf::Vector2f pos) = 0;
    };
}

namespace std
{
    template <>
    struct hash<R_01::CellCoord>
    {
        std::size_t operator()(const R_01::CellCoord &coord) const
        {
            return std::hash<int32_t>()(coord.x) ^ std::hash<int32_t>()(coord.y);
        }
    };
}