#pragma once

#include <SFML/Graphics.hpp>

#include <sim/ant.hpp>
#include <sim/food.hpp>
#include <sim/hive.hpp>
#include <sim/pheromone.hpp>

#include <memory> // std::move, std::shared_ptr

namespace R_01
{
    class World
    {
    private:
        struct M
        {
            sf::Vector2f _Size;

            std::vector<std::shared_ptr<Hive>> _Hives;
            std::vector<std::shared_ptr<Ant>> _Ants;
            std::vector<std::shared_ptr<Food>> _Foods;
            std::vector<std::shared_ptr<Pheromone>> _Pheromones;
        } m;

        explicit World(M m) : m(std::move(m)) {}

    public:
        static World create(float width, float height)
        {
            return World(M{
                ._Size = sf::Vector2f(width, height),

                ._Hives = std::vector<std::shared_ptr<Hive>>(),
                ._Ants = std::vector<std::shared_ptr<Ant>>(),
                ._Foods = std::vector<std::shared_ptr<Food>>(),
                ._Pheromones = std::vector<std::shared_ptr<Pheromone>>()});
        }

        sf::Vector2f getSize() const { return m._Size; }
        std::vector<std::shared_ptr<Hive>> &getHives() { return m._Hives; }
        std::vector<std::shared_ptr<Ant>> &getAnts() { return m._Ants; }
        std::vector<std::shared_ptr<Food>> &getFoods() { return m._Foods; }
        std::vector<std::shared_ptr<Pheromone>> &getPheromones() { return m._Pheromones; }

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
        auto hive = std::make_shared<Hive>(Hive::create(sf::Vector2f(50.0, 50.0), pos, color, 1000, 10));
        
        m._Hives.push_back(std::move(hive));
    }

    void World::spawnAnt(sf::Vector2f pos, sf::Color color, float_t angle, uint32_t health, uint32_t hunger)
    {
        auto ant = std::make_shared<Ant>(Ant::create(sf::Vector2f(10.0, 20.0), pos, color, angle, health, hunger));

        m._Ants.push_back(std::move(ant));
    }

    void World::spawnFood(sf::Vector2f pos, uint32_t nutrition, uint32_t lifespan)
    {
        auto food = std::make_shared<Food>(Food::create(sf::Vector2f(10.0, 10.0), pos, nutrition, lifespan));

        m._Foods.push_back(std::move(food));
    }

    void World::spawnPheromone(sf::Vector2f pos, sf::Color color, float_t angle, float_t strength, uint32_t lifespan)
    {
        auto pheromone = std::make_shared<Pheromone>(Pheromone::create(sf::Vector2f(5.0, 5.0), pos, color, angle, strength, lifespan));

        m._Pheromones.push_back(std::move(pheromone));
    }
}