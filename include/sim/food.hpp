#pragma once

#include <SFML/Graphics.hpp>

#include <sim/object.hpp>

#include <cmath> // std::min

namespace R_01
{
    class Food : public IObject
    {
    private:
        struct M {
            ObjectType _Type;

            sf::Vector2f _Size;
            sf::Vector2f _Pos;
            sf::Color _Color;
            float_t _Hitbox;

            uint32_t _Nutrition;
            uint32_t _Lifespan;
        } m;

        explicit Food(M m) : m(std::move(m)) {}

    public:
        static Food create(sf::Vector2f size, sf::Vector2f pos, uint32_t nutrition, uint32_t lifespan);

        ObjectType getType() const override { return m._Type; }
        sf::Vector2f getPos() const override { return m._Pos; }
        float_t getHitbox() const override { return m._Hitbox; }
        sf::Vector2f getSize() const { return m._Size; }
        sf::Color getColor() const { return m._Color; }
        uint32_t getNutrition() const { return m._Nutrition; }
        uint32_t getLifespan() const { return m._Lifespan; }

        void setPos(sf::Vector2f pos) override { m._Pos = pos; }
    };
}

namespace R_01
{
    Food Food::create(sf::Vector2f size, sf::Vector2f pos, uint32_t nutrition, uint32_t lifespan)
    {
        return Food(M{
            ._Type = ObjectType::FOOD,

            ._Size = size,
            ._Pos = pos,
            ._Color = sf::Color::Green,
            ._Hitbox = 0.0f,

            ._Nutrition = nutrition,
            ._Lifespan = lifespan});
    }
}