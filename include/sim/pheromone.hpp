#pragma once

#include <SFML/Graphics.hpp>

class Pheromone
{
private:
    sf::Vector2f m_BodySize;
    float m_HitboxSize;
    sf::Color m_Color;
    sf::Vector2f m_Position;
    float m_Angle;

    float m_Strength;
    unsigned int m_Lifespan;

public:
    Pheromone(sf::Vector2f bodysize, sf::Color color, sf::Vector2f position, float angle, float strength, unsigned int lifespan);
    ~Pheromone();

    void draw(sf::RenderWindow &window);
    void update();

    float getCollisionRadius() const { return m_HitboxSize; }
    sf::Color getColor() const { return m_Color; }
    sf::Vector2f getPosition() const { return m_Position; }
    float getAngle() const { return m_Angle; }
    float getStrength() const { return m_Strength; }
    unsigned int getLifespan() const { return m_Lifespan; }
};

Pheromone::Pheromone(sf::Vector2f bodysize, sf::Color color, sf::Vector2f position, float angle, float strength, unsigned int lifespan)
    : m_BodySize(bodysize),
      m_HitboxSize(std::min(bodysize.x, bodysize.y) / 2.0f),
      m_Color(color),
      m_Position(position),
      m_Angle(angle),
      m_Strength(strength),
      m_Lifespan(lifespan)
{
}

Pheromone::~Pheromone()
{
}

void Pheromone::draw(sf::RenderWindow &window)
{
    sf::CircleShape body(m_BodySize.x, 3);
    body.setFillColor(m_Color);
    body.setPosition(m_Position);
    body.setRotation(m_Angle + 90.0f);
    body.setOrigin(m_BodySize);
    window.draw(body);
}

void Pheromone::update()
{
    m_Lifespan--;
}