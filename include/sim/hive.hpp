#pragma once

#include <SFML/Graphics.hpp>

#include <vector> // std::vector

class Hive
{
private:
    sf::Vector2f m_BodySize;
    float m_HitboxSize;
    sf::Color m_Color;

    sf::Vector2f m_Position;

    unsigned int m_AntSpawnRate;

    unsigned int m_FoodStored;

public:
    Hive(sf::Color color, sf::Vector2f position, unsigned int maxAntCount, unsigned int antSpawnRate);
    ~Hive();

    void draw(sf::RenderWindow &window);
    void update();

    sf::Vector2f getSize() const { return m_BodySize; }
    float getCollisionRadius() const { return m_HitboxSize; }
    sf::Color getColor() const { return m_Color; }
    sf::Vector2f getPosition() const { return m_Position; }
    unsigned int getAntSpawnRate() const { return m_AntSpawnRate; }
    unsigned int getFoodStored() const { return m_FoodStored; }

    void storeFood(float nutrition);
};

Hive::Hive(sf::Color color, sf::Vector2f position, unsigned int maxAntCount, unsigned int antSpawnRate)
    : m_BodySize(sf::Vector2f(100.0f, 100.0f)),
      m_HitboxSize(100.0f),
      m_Color(color),
      m_Position(position),
      m_AntSpawnRate(antSpawnRate),
      m_FoodStored(0)
{
}

Hive::~Hive() {}

void Hive::draw(sf::RenderWindow &window)
{
    sf::CircleShape hive(m_BodySize.x, 60);
    hive.setFillColor(m_Color);
    hive.setOutlineColor(sf::Color(255, 255, 255, 255));
    hive.setOutlineThickness(5.0);
    hive.setOrigin(m_BodySize);
    hive.setPosition(m_Position);
    window.draw(hive);
}

void Hive::update()
{
}

void Hive::storeFood(float nutrition)
{
    m_FoodStored += nutrition;
}