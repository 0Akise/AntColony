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
        static World create(float width, float height);
        static World create(sf::Vector2f size);

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
    World World::create(float width, float height)
    {
        return World(M{
            ._Size = sf::Vector2f(width, height),

            ._Hives = std::vector<Hive>(),
            ._Ants = std::vector<Ant>(),
            ._Foods = std::vector<Food>(),
            ._Pheromones = std::vector<Pheromone>()});
    }

    World World::create(sf::Vector2f size)
    {
        return World(M{
            ._Size = size,

            ._Hives = std::vector<Hive>(),
            ._Ants = std::vector<Ant>(),
            ._Foods = std::vector<Food>(),
            ._Pheromones = std::vector<Pheromone>()});
    }

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

/*
void World::draw(sf::RenderWindow &window, sf::Vector2f worldPos, ResourceVault &vault)
{
    sf::RectangleShape shape(sf::Vector2f(m_WorldWidth, m_WorldHeight));
    shape.setOutlineColor(sf::Color(255, 255, 255, 255));
    shape.setOutlineThickness(5.0);
    shape.setFillColor(sf::Color(51, 51, 51, 255));
    shape.setPosition(sf::Vector2f(worldPos.x, worldPos.y));
    window.draw(shape);

    for (auto &hive : m_Hives)
    {
        hive.draw(window);
    }

    for (auto &ant : m_Ants)
    {
        ant.draw(window, vault.antTexture);
    }

    for (auto &food : m_Foods)
    {
        food.draw(window);
    }

    for (auto &pheromone : m_Pheromones)
    {
        pheromone.draw(window);
    }

    for (auto &hive : m_Hives)
    {
        unsigned int antCount = 0;

        for (auto &ant : m_Ants)
        {
            if (ant.getHive() == &hive)
            {
                antCount++;
            }
        }

        sf::Text textAntCount;
        textAntCount.setFont(vault.font);
        textAntCount.setString(std::to_string(antCount));
        textAntCount.setCharacterSize(16);
        textAntCount.setFillColor(sf::Color::Black);
        textAntCount.setPosition(hive.getPosition());
        textAntCount.setOrigin(textAntCount.getLocalBounds().getSize() / 2.0f);
        window.draw(textAntCount);

        m_AntCount = antCount;
    }
}

void World::update()
{
    m_HiveGrid.clear();
    m_AntGrid.clear();
    m_FoodGrid.clear();
    m_PheromoneGrid.clear();

    for (auto &hive : m_Hives)
    {
        insertHive(&hive, m_CellSize);

        hive.update();
    }

    for (auto &ant : m_Ants)
    {
        insertAnt(&ant, m_CellSize);

        if (ant.getIsCarryingFood())
            spawnPheromone(&ant, 0.5f, 100.0f);

        ant.update();
    }

    for (auto &food : m_Foods)
    {
        insertFood(&food, m_CellSize);

        food.update();
    }

    for (auto &pheromone : m_Pheromones)
    {
        insertPheromone(&pheromone, m_CellSize);

        pheromone.update();
    }

    if (m_AntCount < 500)
    {
        for (std::size_t i = 0; i < m_Hives.size(); i++)
        {
            spawnAnt(i);
        }
    }

    checkAntsCollision();
    checkAntsBorderCollision();
    checkAntHiveCollision();
    checkAntFoodCollision();
    checkAntsFollowPheromone();
    checkRemove();
}

void World::spawnHive(sf::Color color, sf::Vector2f position, unsigned int maxAntCount, unsigned int antSpawnRate)
{
    m_Hives.push_back(Hive(color, position, maxAntCount, antSpawnRate));
}

void World::spawnAnt(unsigned int hiveIndex)
{
    sf::Vector2f antSize(10.0f, 20.0f);
    sf::Color antColor = m_Hives[hiveIndex].getColor();

    sf::Vector2f antPos(sf::Vector2f(
        (m_Hives[hiveIndex].getPosition().x) + std::cos(MathUtil::degtorad(rand() % 360)) * m_Hives[hiveIndex].getCollisionRadius(),
        (m_Hives[hiveIndex].getPosition().y) + std::sin(MathUtil::degtorad(rand() % 360)) * m_Hives[hiveIndex].getCollisionRadius()));

    float antVelocity = 1.0f;
    float antAngle = rand() % 360;
    unsigned int antHealth = 100;
    unsigned int antHunger = 100;

    m_Ants.push_back(Ant(antSize, antColor, antPos, antVelocity, antAngle, antHealth, antHunger, &m_Hives[hiveIndex]));
}

void World::spawnFood(sf::Vector2f position, float nutrition, unsigned int lifespan)
{
    sf::Vector2f foodSize(5.0f, 5.0f);

    m_Foods.push_back(Food(foodSize, position, nutrition, lifespan));
}

void World::spawnPheromone(Ant *ant, float strength, float lifespan)
{
    sf::Vector2f pheromoneSize(3.0f, 3.0f);
    sf::Color pheromoneColor = ant->getColor();
    sf::Vector2f pheromonePos = ant->getPosition();
    float pheromoneAngle = ant->getAngle() + 180.0f;

    pheromoneColor.a = 30;

    if (rand() % 2)
        m_Pheromones.push_back(Pheromone(pheromoneSize, pheromoneColor, pheromonePos, pheromoneAngle, strength, lifespan));
}

void World::insertHive(Hive *hive, float cellSize)
{
    CellCoord cell = {
        static_cast<int>(hive->getPosition().x / cellSize),
        static_cast<int>(hive->getPosition().y / cellSize)};

    m_HiveGrid[cell].push_back(hive);
}

void World::insertAnt(Ant *ant, float cellSize)
{
    CellCoord cell = {
        static_cast<int>(ant->getPosition().x / cellSize),
        static_cast<int>(ant->getPosition().y / cellSize)};

    m_AntGrid[cell].push_back(ant);
}

void World::insertFood(Food *food, float cellSize)
{
    CellCoord cell = {
        static_cast<int>(food->getPosition().x / cellSize),
        static_cast<int>(food->getPosition().y / cellSize)};

    m_FoodGrid[cell].push_back(food);
}

void World::insertPheromone(Pheromone *pheromone, float cellSize)
{
    CellCoord cell = {
        static_cast<int>(pheromone->getPosition().x / cellSize),
        static_cast<int>(pheromone->getPosition().y / cellSize)};

    m_PheromoneGrid[cell].push_back(pheromone);
}

bool World::areAntsColliding(Ant *ant1, Ant *ant2)
{
    sf::Vector2f ant1Pos = ant1->getPosition();
    sf::Vector2f ant2Pos = ant2->getPosition();
    float distance = MathUtil::distance(ant1Pos, ant2Pos);

    return distance < (ant1->getCollisionRadius() + ant2->getCollisionRadius());
}

bool World::isAntCollidingWithHive(Ant *ant, Hive *hive)
{
    sf::Vector2f antPos = ant->getPosition();
    sf::Vector2f hivePos = hive->getPosition();
    float distance = MathUtil::distance(antPos, hivePos);

    return distance < (ant->getCollisionRadius() + hive->getCollisionRadius());
}

bool World::isAntCollidingWithFood(Ant *ant, Food *food)
{
    sf::Vector2f antPos = ant->getPosition();
    sf::Vector2f foodPos = food->getPosition();
    float distance = MathUtil::distance(antPos, foodPos);

    return distance < (ant->getCollisionRadius() + food->getCollisionRadius());
}

bool World::isAntOnPheromone(Ant *ant, Pheromone *pheromone)
{
    sf::Vector2f antPos = ant->getPosition();
    sf::Vector2f pheromonePos = pheromone->getPosition();
    float distance = MathUtil::distance(antPos, pheromonePos);

    return distance < (ant->getCollisionRadius() + pheromone->getCollisionRadius());
}

void World::checkAntsCollision()
{
    for (auto &entry : m_AntGrid)
    {
        const CellCoord &coord = entry.first;
        const std::vector<Ant *> &ants = entry.second;

        for (std::size_t i = 0; i < ants.size(); ++i)
        {
            for (std::size_t j = i + 1; j < ants.size(); ++j)
            {
                if ((ants[i] != ants[j]) && areAntsColliding(ants[i], ants[j]))
                {
                    sf::Vector2f direction = ants[i]->getPosition() - ants[j]->getPosition();
                    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                    direction /= magnitude;

                    ants[i]->setPosition(ants[i]->getPosition() + direction * 0.25f);
                    ants[j]->setPosition(ants[j]->getPosition() - direction * 0.25f);
                }
            }
        }

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;

                CellCoord neighbor = {coord.x + dx, coord.y + dy};
                auto neighborIt = m_AntGrid.find(neighbor);

                if (neighborIt != m_AntGrid.end())
                {
                    for (auto *ant : ants)
                    {
                        for (auto *neighborAnt : neighborIt->second)
                        {
                            if (areAntsColliding(ant, neighborAnt))
                            {
                                sf::Vector2f direction = ant->getPosition() - neighborAnt->getPosition();
                                float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                                direction /= magnitude;

                                ant->setPosition(ant->getPosition() + direction * 0.25f);
                                neighborAnt->setPosition(neighborAnt->getPosition() - direction * 0.25f);
                            }
                        }
                    }
                }
            }
        }
    }
}

void World::checkAntsBorderCollision()
{
    for (auto &ant : m_Ants)
    {
        sf::Vector2f antPos = ant.getPosition();
        float antAngle = ant.getAngle();

        if (antPos.x < 0.0)
        {
            antPos.x = 0.0;
            antAngle = antAngle + 180.0;
        }
        else if (antPos.x > m_WorldWidth)
        {
            antPos.x = m_WorldWidth;
            antAngle = antAngle - 180.0;
        }

        if (antPos.y < 0.0)
        {
            antPos.y = 0.0;
            antAngle = antAngle + 180.0;
        }
        else if (antPos.y > m_WorldHeight)
        {
            antPos.y = m_WorldHeight;
            antAngle = antAngle - 180.0;
        }

        ant.setPosition(antPos);
        ant.setAngle(antAngle);
    }
}

void World::checkAntHiveCollision()
{
    for (auto &antEntry : m_AntGrid)
    {
        const CellCoord &antCoord = antEntry.first;
        const std::vector<Ant *> &ants = antEntry.second;

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                CellCoord hiveCoord = {antCoord.x + dx, antCoord.y + dy};
                auto hiveIt = m_HiveGrid.find(hiveCoord);

                if (hiveIt != m_HiveGrid.end())
                {
                    for (auto *ant : ants)
                    {
                        for (auto *hive : hiveIt->second)
                        {
                            if (isAntCollidingWithHive(ant, hive))
                            {
                                ant->setIsCarryingFood(false);
                                hive->storeFood(100.0);

                                sf::Vector2f direction = ant->getPosition() - hive->getPosition();
                                float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                                direction /= magnitude;

                                ant->setPosition(ant->getPosition() + direction);
                            }
                        }
                    }
                }
            }
        }
    }
}

void World::checkAntFoodCollision()
{
    for (auto &antEntry : m_AntGrid)
    {
        const CellCoord &antCoord = antEntry.first;
        const std::vector<Ant *> &ants = antEntry.second;

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                CellCoord foodCoord = {antCoord.x + dx, antCoord.y + dy};
                auto foodIt = m_FoodGrid.find(foodCoord);

                if (foodIt != m_FoodGrid.end())
                {
                    for (auto *ant : ants)
                    {
                        if (!ant->getIsCarryingFood())
                        {
                            for (auto *food : foodIt->second)
                            {
                                if (isAntCollidingWithFood(ant, food))
                                {
                                    ant->setIsCarryingFood(true);
                                    food->setLifeSpan(0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void World::checkAntsFollowPheromone()
{
    for (auto &antEntry : m_AntGrid)
    {
        const CellCoord &antCoord = antEntry.first;
        const std::vector<Ant *> &ants = antEntry.second;

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                CellCoord pheromoneCoord = {antCoord.x + dx, antCoord.y + dy};
                auto pheromoneIt = m_PheromoneGrid.find(pheromoneCoord);

                if (pheromoneIt != m_PheromoneGrid.end())
                {
                    for (auto *ant : ants)
                    {
                        for (auto *pheromone : pheromoneIt->second)
                        {
                            if ((isAntOnPheromone(ant, pheromone)) && (!ant->getIsCarryingFood()))
                            {
                                ant->setAngle(pheromone->getAngle());
                            }
                        }
                    }
                }
            }
        }
    }
}

void World::checkRemove()
{
    if (m_Foods.size() > 0)
    {
        for (std::size_t i = 0; i < m_Foods.size(); i++)
        {
            if (m_Foods[i].getLifespan() <= 0)
            {
                m_Foods.erase(m_Foods.begin() + i);
            }
        }
    }

    if (m_Pheromones.size() > 0)
    {
        for (std::size_t i = 0; i < m_Pheromones.size(); i++)
        {
            if (m_Pheromones[i].getLifespan() <= 0)
            {
                m_Pheromones.erase(m_Pheromones.begin() + i);
            }
        }
    }
}
*/