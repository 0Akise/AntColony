#pragma once

#include <SFML/Graphics.hpp>

#include <sim/object.hpp>

#include <cmath> // std::min

namespace R_01
{
    class Pheromone : public IObject
    {
    private:
        struct M
        {
            ObjectType _Type;

            sf::Vector2f _Size;
            sf::Vector2f _Pos;
            sf::Color _Color;
            float_t _Hitbox;
            float_t _Angle;

            float_t _Strength;
            uint32_t _Lifespan;
        } m;

        explicit Pheromone(M m) : m(std::move(m)) {}

    public:
        static Pheromone create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, float_t angle, float_t strength, uint32_t lifespan)
        {
            return Pheromone(M{
                ._Type = ObjectType::PHEROMONE,

                ._Size = size,
                ._Pos = pos,
                ._Color = color,
                ._Hitbox = 0.0f,
                ._Angle = angle,

                ._Strength = strength,
                ._Lifespan = lifespan});
        }

        ObjectType getType() const override { return m._Type; }
        sf::Vector2f getPos() const override { return m._Pos; }
        float_t getHitbox() const override { return m._Hitbox; }
        sf::Vector2f getSize() const { return m._Size; }
        sf::Color getColor() const { return m._Color; }
        float_t getAngle() const { return m._Angle; }
        float_t getStrength() const { return m._Strength; }
        uint32_t getLifespan() const { return m._Lifespan; }

        void setPos(sf::Vector2f pos) override { m._Pos = pos; }
    };
}