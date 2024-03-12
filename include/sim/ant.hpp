#pragma once

#include <SFML/Graphics.hpp>

#include <sim/food.hpp>
#include <sim/pheromone.hpp>
#include <sim/hive.hpp>
#include <util.hpp>

#include <cmath> // std::cos, std::sin

class Ant
{
private:
    sf::Vector2f m_BodySize;
    float m_HitboxSize;
    sf::Color m_Color;

    sf::Vector2f m_Position;
    float m_Velocity;
    float m_Angle;

    unsigned int m_Health;
    unsigned int m_Hunger;

    bool m_IsCarryingFood;

    Hive *m_Hive;

public:
    Ant(sf::Vector2f bodysize, sf::Color color, sf::Vector2f position, float velocity, float angle, unsigned int health, unsigned int hunger, Hive *hive);
    ~Ant();

    void draw(sf::RenderWindow &window, const sf::Texture &texture);
    void update();

    sf::Color getColor() const { return m_Color; }
    sf::Vector2f getPosition() const { return m_Position; }
    float getAngle() const { return m_Angle; }
    float getCollisionRadius() const { return m_HitboxSize; }
    bool getIsCarryingFood() const { return m_IsCarryingFood; }
    Hive *getHive() const { return m_Hive; }
    void setPosition(sf::Vector2f position) { m_Position = position; }
    void setAngle(float angle) { m_Angle = angle; }
    void setIsCarryingFood(bool isCarryingFood) { m_IsCarryingFood = isCarryingFood; }
};

Ant::Ant(sf::Vector2f bodysize, sf::Color color, sf::Vector2f position, float velocity, float angle, unsigned int health, unsigned int hunger, Hive *hive)
    : m_BodySize(bodysize),
      m_HitboxSize(std::min(bodysize.x, bodysize.y) / 2.0f),
      m_Color(color),
      m_Position(position),
      m_Velocity(velocity),
      m_Angle(angle),
      m_Health(health),
      m_Hunger(hunger),
      m_IsCarryingFood(false),
      m_Hive(hive)
{
}

Ant::~Ant() {}

void Ant::draw(sf::RenderWindow &window, const sf::Texture &texture)
{
    sf::RectangleShape ant(m_BodySize);
    ant.setTexture(&texture);
    ant.setFillColor(m_Color);
    ant.setPosition(m_Position);
    ant.setRotation(m_Angle + 90.0f);
    ant.setOrigin(m_BodySize.x / 2.0f, m_BodySize.y / 2.0f);
    window.draw(ant);

    if (m_IsCarryingFood)
    {
        sf::CircleShape food(5.0f);
        food.setFillColor(sf::Color::Green);
        food.setPosition(m_Position);
        window.draw(food);
    }
}

void Ant::update()
{
    m_Position.x += m_Velocity * std::cos(MathUtil::degtorad(m_Angle));
    m_Position.y += m_Velocity * std::sin(MathUtil::degtorad(m_Angle));

    if (m_IsCarryingFood)
    {
        m_Angle = MathUtil::lerpangle(m_Angle, MathUtil::radtodeg(MathUtil::pointtowards(m_Position, m_Hive->getPosition())), 0.1f);
    }
}