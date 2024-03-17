#pragma once

#include <sim/_sim.hpp>
#include <ui/_ui.hpp>
#include <control.hpp>
#include <resvault.hpp>

#include <memory>        // std::move, std::unique_ptr
#include <unordered_map> // std::unordered_map
#include <iostream>      // std::cout, std::endl

namespace R_01
{
    class Program
    {
    private:
        struct M
        {
            uint32_t _Ticks;
            sf::Clock _FrametimeClock;
            ResourceVault _Vault;
            Control _Control;

            int32_t _FabricSize;
            World _World;
            std::unordered_map<CellCoord, std::vector<std::unique_ptr<IObject>>> _Field;
        } m;

        explicit Program(M m) : m(std::move(m)) {}

    public:
        static Program Create(sf::RenderWindow &window)
        {
            return Program(M{
                ._Ticks = 0,
                ._FrametimeClock = sf::Clock(),
                ._Vault = ResourceVault(),

                ._Control = Control::create(),

                ._FabricSize = 10,
                ._World = World::create(4000.0, 3000.0),
                ._Field = std::unordered_map<CellCoord, std::vector<std::unique_ptr<IObject>>>()});
        }

        void InitWorld();
        void InsertObject(std::unique_ptr<IObject> obj, int32_t fabricSize);
        bool CheckCollision(IObject *obj1, IObject *obj2);
        void HandleCollision();

        void Move(sf::RenderWindow &window, sf::Vector2f cameraPos, float cameraZoom);
        void Render(sf::RenderWindow &window);
        void Ui(sf::RenderWindow &window, sf::Vector2f screen);
        void Update(uint32_t ticks);
        void Run(sf::RenderWindow &window);
    };
}

namespace R_01
{
    void Program::InitWorld()
    {
        m._World.spawnHive(sf::Vector2f(200.0, 200.0), sf::Color(255, 0, 0, 255));
        // m._World.spawnHive(sf::Vector2f(2400.0, 1500.0), sf::Color(0, 255, 0, 255));
    }

    void Program::InsertObject(std::unique_ptr<IObject> obj, int32_t fabricSize)
    {
        CellCoord coord = {
            static_cast<int32_t>(obj->getPos().x / fabricSize),
            static_cast<int32_t>(obj->getPos().y / fabricSize)};

        m._Field[coord].push_back(std::move(obj));
    }

    bool Program::CheckCollision(IObject *obj1, IObject *obj2)
    {
        auto pos1 = obj1->getPos();
        auto pos2 = obj2->getPos();
        auto hitbox1 = obj1->getHitbox();
        auto hitbox2 = obj2->getHitbox();
        float distance = MathUtil::distance(pos1, pos2);

        return distance < (hitbox1 + hitbox2);
    }

    void Program::HandleCollision()
    {
        // this does not work
        for (auto &[coord, objects] : m._Field)
        {
            for (auto &obj: objects)
            {
                if (obj->getType() == ObjectType::ANT)
                {
                    if (obj->getPos().x < 0.0)
                        obj->setPos(sf::Vector2f(0.0, obj->getPos().y));
                    if (obj->getPos().x > m._World.getSize().x)
                        obj->setPos(sf::Vector2f(m._World.getSize().x, obj->getPos().y));
                    if (obj->getPos().y < 0.0)
                        obj->setPos(sf::Vector2f(obj->getPos().x, 0.0));
                    if (obj->getPos().y > m._World.getSize().y)
                        obj->setPos(sf::Vector2f(obj->getPos().x, m._World.getSize().y));
                }
            }
        }

        /* this works
        for (auto &ant : m._World.getAnts())
        {
            if (ant.getPos().x < 0.0)
                ant.setPos(sf::Vector2f(0.0, ant.getPos().y));
            if (ant.getPos().x > m._World.getSize().x)
                ant.setPos(sf::Vector2f(m._World.getSize().x, ant.getPos().y));
            if (ant.getPos().y < 0.0)
                ant.setPos(sf::Vector2f(ant.getPos().x, 0.0));
            if (ant.getPos().y > m._World.getSize().y)
                ant.setPos(sf::Vector2f(ant.getPos().x, m._World.getSize().y));

            for (auto &hive : m._World.getHives())
            {
                if (CheckCollision(&ant, &hive))
                {
                    sf::Vector2f direction = ant.getPos() - hive.getPos();
                    float magnitude = MathUtil::magnitude(direction);
                    
                    direction /= magnitude;

                    ant.setPos(ant.getPos() + direction);
                }
            }

            for (auto &otherAnt : m._World.getAnts())
            {
                if ((&ant != &otherAnt) && CheckCollision(&ant, &otherAnt))
                {
                    sf::Vector2f direction = ant.getPos() - otherAnt.getPos();
                    float magnitude = MathUtil::magnitude(direction);

                    direction /= magnitude;

                    ant.setPos(ant.getPos() + direction * 0.25f);
                    otherAnt.setPos(otherAnt.getPos() - direction * 0.25f);
                }
            }
        }*/
    }
}

namespace R_01
{
    void Program::Move(sf::RenderWindow &window, sf::Vector2f cameraPos, float cameraZoom)
    {
        sf::View view = window.getView();

        view.setCenter(cameraPos);
        view.setSize(window.getSize().x * cameraZoom, window.getSize().y * cameraZoom);
        window.setView(view);
    }

    void Program::Render(sf::RenderWindow &window)
    {
        sf::RectangleShape worldShape(m._World.getSize());
        worldShape.setOutlineColor(sf::Color(255, 255, 255, 255));
        worldShape.setOutlineThickness(5.0);
        worldShape.setFillColor(sf::Color(51, 51, 51, 255));
        worldShape.setPosition(sf::Vector2f(0.0f, 0.0f));
        window.draw(worldShape);

        for (auto &hive : m._World.getHives())
        {
            sf::CircleShape hiveShape(hive.getSize().x, 60);
            hiveShape.setOutlineColor(sf::Color(255, 255, 255, 255));
            hiveShape.setOutlineThickness(5.0);
            hiveShape.setFillColor(hive.getColor());
            hiveShape.setPosition(hive.getPos());
            hiveShape.setOrigin(hive.getSize().x, hive.getSize().y);
            window.draw(hiveShape);
        }

        for (auto &ant : m._World.getAnts())
        {
            sf::RectangleShape antShape(ant.getSize());
            antShape.setTexture(&m._Vault.antTexture);
            antShape.setFillColor(ant.getColor());
            antShape.setPosition(ant.getPos());
            antShape.setRotation(ant.getAngle() + 90.0f);
            antShape.setOrigin(ant.getSize().x / 2, ant.getSize().y / 2);
            window.draw(antShape);
        }
    }

    void Program::Ui(sf::RenderWindow &window, sf::Vector2f screen)
    {
        sf::Text text;
        text.setFont(m._Vault.font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setString("FPS: " + std::to_string(1.0f / m._FrametimeClock.restart().asSeconds()));
        text.setPosition(10.0f, 10.0f);
        window.draw(text);
    }

    void Program::Update(uint32_t ticks)
    {
        m._Field.clear();

        for (auto &hive : m._World.getHives())
        {
            InsertObject(std::make_unique<Hive>(hive), m._FabricSize);
        }

        for (auto &ant : m._World.getAnts())
        {
            InsertObject(std::make_unique<Ant>(ant), m._FabricSize);

            ant.think();
        }

        for (auto &hive : m._World.getHives())
        {
            if (ticks % hive.getAntSpawnRate() == 0)
            {
                sf::Vector2f antPos = sf::Vector2f(
                    (hive.getPos().x) + std::cos(MathUtil::degtorad(rand() % 360)) * hive.getHitbox(),
                    (hive.getPos().y) + std::sin(MathUtil::degtorad(rand() % 360)) * hive.getHitbox());

                m._World.spawnAnt(antPos, hive.getColor(), std::rand() % 360, 100, 100);
            }
        }

        HandleCollision();
    }

    void Program::Run(sf::RenderWindow &window)
    {
        InitWorld();

        while (window.isOpen())
        {
            window.clear();
            m._Control.process(window);

            if (m._Control.getState() == ProgramState::Running)
            {
                Update(m._Ticks);
                m._Ticks++;
            }

            Move(window, m._Control.getCameraPos(), m._Control.getCameraZoom());
            Render(window);

            Move(window, window.getDefaultView().getCenter(), 1.0);
            Ui(window, window.getView().getSize());

            window.display();
        }
    }
}