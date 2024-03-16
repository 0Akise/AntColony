#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace R_01
{
    enum class ProgramState
    {
        Paused,
        Running,
    };
    
    class Control
    {
    private:
        struct M
        {
            ProgramState _State;

            sf::Vector2f _CameraPos;
            float _CameraZoom;

            bool _IsDraggingLeftMouse;
            sf::Vector2i _LastLeftMousePos;

            bool _IsDraggingRightMouse;
            sf::Vector2i _LastRightMousePos;
        } m;

        explicit Control(M m) : m(std::move(m)) {}

    public:
        static Control create();

        ProgramState getState() const { return m._State; }
        sf::Vector2f getCameraPos() const { return m._CameraPos; }
        float getCameraZoom() const { return m._CameraZoom; }

        void process(sf::RenderWindow &window);
    };
}

namespace R_01
{
    Control Control::create()
    {
        return Control(M{
            ._State = ProgramState::Paused,

            ._CameraPos = sf::Vector2f(0.0, 0.0),
            ._CameraZoom = 1.0,

            ._IsDraggingLeftMouse = false,
            ._LastLeftMousePos = sf::Vector2i(0, 0),
            ._IsDraggingRightMouse = false,
            ._LastRightMousePos = sf::Vector2i(0, 0)});
    }

    void Control::process(sf::RenderWindow &window)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {
                if (m._State == ProgramState::Paused)
                {
                    m._State = ProgramState::Running;
                }
                else
                {
                    m._State = ProgramState::Paused;
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    m._CameraZoom *= 0.9f;
                }
                else
                {
                    m._CameraZoom *= 1.1f;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m._IsDraggingLeftMouse = true;
                    m._LastLeftMousePos = sf::Mouse::getPosition(window);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m._IsDraggingLeftMouse = false;
                }
            }

            if ((event.type == sf::Event::MouseMoved))
            {
                if (m._IsDraggingLeftMouse)
                {
                    sf::Vector2i currentPos = sf::Mouse::getPosition(window);
                    sf::Vector2i difference = currentPos - m._LastLeftMousePos;

                    m._CameraPos.x -= difference.x * m._CameraZoom;
                    m._CameraPos.y -= difference.y * m._CameraZoom;

                    m._LastLeftMousePos = currentPos;
                }
            }
        }
    }
}