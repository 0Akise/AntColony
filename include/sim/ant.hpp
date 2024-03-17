#pragma once

#include <SFML/Graphics.hpp>

#include <sim/object.hpp>
#include <util.hpp>

#include <cmath> // std::min
#include <iostream>

namespace R_01
{
    class Ant : public IObject
    {
    private:
        struct M
        {
            ObjectType _Type;

            sf::Vector2f _Size;
            sf::Vector2f _Pos;
            sf::Color _Color;
            float_t _Hitbox;

            float_t _Velocity;
            float_t _Angle;

            uint32_t _Health;
            uint32_t _Hunger;

            bool _IsCarryingFood;
        } m;

        explicit Ant(M m) : m(std::move(m)) {}

    public:
        static Ant create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, float_t angle, uint32_t health, uint32_t hunger)
        {
            return Ant(M{
                ._Type = ObjectType::ANT,

                ._Size = size,
                ._Pos = pos,
                ._Color = color,
                ._Hitbox = std::min(size.x, size.y) / 2.0f,

                ._Velocity = 1.0f,
                ._Angle = angle,

                ._Health = health,
                ._Hunger = hunger,

                ._IsCarryingFood = false});
        }

        ~Ant() = default;

        void think();

        ObjectType getType() const override { return m._Type; }
        sf::Vector2f getPos() const override { return m._Pos; }
        float_t getHitbox() const override { return m._Hitbox; }
        sf::Vector2f getSize() const { return m._Size; }
        sf::Color getColor() const { return m._Color; }
        float_t getVelocity() const { return m._Velocity; }
        float_t getAngle() const { return m._Angle; }
        uint32_t getHealth() const { return m._Health; }
        uint32_t getHunger() const { return m._Hunger; }
        bool getIsCarryingFood() const { return m._IsCarryingFood; }

        void setPos(sf::Vector2f pos) override { m._Pos = pos; }
        void setVelocity(float_t velocity) { m._Velocity = velocity; }
        void setAngle(float_t angle) { m._Angle = angle; }
        void setHealth(uint32_t health) { m._Health = health; }
        void setHunger(uint32_t hunger) { m._Hunger = hunger; }
    };
}

namespace R_01
{
    void Ant::think()
    {
        m._Pos.x += m._Velocity * std::cos(MathUtil::degtorad(m._Angle));
        m._Pos.y += m._Velocity * std::sin(MathUtil::degtorad(m._Angle));

        m._Angle += (std::rand() % 3) - 1;
    }
}