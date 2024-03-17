#pragma once

#include <SFML/Graphics.hpp>

#include <sim/object.hpp>

#include <cmath> // std::min

namespace R_01
{
    class Hive : public IObject
    {
    private:
        struct M
        {
            ObjectType _Type;

            sf::Vector2f _Size;
            sf::Vector2f _Pos;
            sf::Color _Color;
            float_t _Hitbox;

            uint32_t _HitPoints;
            uint32_t _AntSpawnRate;
            uint32_t _FoodStored;
        } m;

        explicit Hive(M m) : m(std::move(m)) {}

    public:
        static Hive create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, uint32_t hitPoints, uint32_t antSpawnRate)
        {
            return Hive(M{
                ._Type = ObjectType::HIVE,

                ._Size = size,
                ._Pos = pos,
                ._Color = color,
                ._Hitbox = std::min(size.x, size.y),

                ._HitPoints = hitPoints,
                ._AntSpawnRate = antSpawnRate,
                ._FoodStored = 0});
        }

        ~Hive() = default;

        ObjectType getType() const override { return m._Type; }
        sf::Vector2f getPos() const override { return m._Pos; }
        float_t getHitbox() const override { return m._Hitbox; }
        sf::Vector2f getSize() const { return m._Size; }
        sf::Color getColor() const { return m._Color; }
        uint32_t getHitPoints() const { return m._HitPoints; }
        uint32_t getAntSpawnRate() const { return m._AntSpawnRate; }
        uint32_t getFoodStored() const { return m._FoodStored; }

        void setPos(sf::Vector2f pos) override { m._Pos = pos; }
    };
}