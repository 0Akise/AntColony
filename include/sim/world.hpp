#pragma once

#include <SFML/Graphics.hpp>

#include <sim/ant.hpp>
#include <sim/food.hpp>
#include <sim/hive.hpp>
#include <sim/pheromone.hpp>

namespace R_01
{
    class World
    {
    private:
        struct M
        {
            sf::Vector2f _Size;

            std::vector<Hive> _Hives;
            std::vector<Ant> _Ants;
            std::vector<Food> _Foods;
            std::vector<Pheromone> _Pheromones;
        } m;

        explicit World(M m) : m(std::move(m)) {}

    public:
        static World create(float width, float height)
        {
            return World(M{
                ._Size = sf::Vector2f(width, height),

                ._Hives = std::vector<Hive>(),
                ._Ants = std::vector<Ant>(),
                ._Foods = std::vector<Food>(),
                ._Pheromones = std::vector<Pheromone>()});
        }

        sf::Vector2f getSize() const { return m._Size; }
        std::vector<Hive> &getHives() { return m._Hives; }
        std::vector<Ant> &getAnts() { return m._Ants; }
        std::vector<Food> &getFoods() { return m._Foods; }
        std::vector<Pheromone> &getPheromones() { return m._Pheromones; }

        void spawnHive(sf::Vector2f pos, sf::Color color);
        void spawnAnt(sf::Vector2f pos, sf::Color color, float_t angle, uint32_t health, uint32_t hunger);
        void spawnFood(sf::Vector2f pos, uint32_t nutrition, uint32_t lifespan);
        void spawnPheromone(sf::Vector2f pos, sf::Color color, float_t angle, float_t strength, uint32_t lifespan);
    };
}

namespace R_01
{
    void World::spawnHive(sf::Vector2f pos, sf::Color color)
    {
        m._Hives.push_back(Hive::create(sf::Vector2f(50.0f, 50.0f), pos, color, 10000, 5));
    }

    void World::spawnAnt(sf::Vector2f pos, sf::Color color, float_t angle, uint32_t health, uint32_t hunger)
    {
        m._Ants.push_back(Ant::create(sf::Vector2f(10.0f, 20.0f), pos, color, angle, health, hunger));
    }

    void World::spawnFood(sf::Vector2f pos, uint32_t nutrition, uint32_t lifespan)
    {
        m._Foods.push_back(Food::create(sf::Vector2f(5.0f, 5.0f), pos, nutrition, lifespan));
    }

    void World::spawnPheromone(sf::Vector2f pos, sf::Color color, float_t angle, float_t strength, uint32_t lifespan)
    {
        m._Pheromones.push_back(Pheromone::create(sf::Vector2f(3.0f, 3.0f), pos, color, angle, strength, lifespan));
    }
}