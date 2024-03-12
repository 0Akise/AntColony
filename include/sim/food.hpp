#pragma once

#include <SFML/Graphics.hpp>

class Food
{
private:
    sf::Vector2f m_BodySize;
    float m_HitboxSize;
    sf::Vector2f m_Position;

    float m_Nutrition;
    unsigned int m_Lifespan;

public:
    Food(sf::Vector2f bodysize, sf::Vector2f position, float hungerValue, unsigned int lifespan);
    ~Food();

    void draw(sf::RenderWindow &window);
    void update();

    sf::Vector2f getBodySize() const { return m_BodySize; }
    float getCollisionRadius() const { return m_HitboxSize; }
    sf::Vector2f getPosition() const { return m_Position; }
    float getHungerValue() const { return m_Nutrition; }
    unsigned int getLifespan() const { return m_Lifespan; }
    void setLifeSpan(unsigned int lifespan) { m_Lifespan = lifespan; }
};

Food::Food(sf::Vector2f bodysize, sf::Vector2f position, float nutrition, unsigned int lifespan)
    : m_BodySize(bodysize),
      m_HitboxSize(std::min(bodysize.x, bodysize.y) / 2.0f),
      m_Position(position),
      m_Nutrition(nutrition),
      m_Lifespan(lifespan)
{
}

Food::~Food()
{
}

void Food::draw(sf::RenderWindow &window)
{
    sf::CircleShape body(m_BodySize.x);
    body.setFillColor(sf::Color::Green);
    body.setPosition(m_Position);
    body.setOrigin(m_BodySize);
    window.draw(body);
}

void Food::update()
{
}