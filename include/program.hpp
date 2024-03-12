#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <sim/world.hpp>
#include <camera.hpp>
#include <resvault.hpp>

#include <memory>  // std::unique_ptr
#include <cstring> // std::string

enum class ProgramState
{
    Paused,
    Running,
};

class Program
{
private:
    sf::RenderWindow m_Window;
    unsigned int Ticks;
    sf::Clock m_FrameTimeClock;
    ProgramState m_State;
    ResourceVault m_Vault;

    World m_World;
    sf::Vector2f m_WorldPos;

    Camera m_Camera;
    sf::Vector2f m_CameraPos;

    unsigned int m_CurrentHiveIndex;
    unsigned int m_CurrentAntIndex;

public:
    Program();
    ~Program();

    void control();
    void paint(float scrW, float scrH);
    void run();
};

Program::Program()
    : m_Window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "My Research 1: Ant Colony", sf::Style::None),
      Ticks(0),
      m_FrameTimeClock(),
      m_State(ProgramState::Paused),
      m_Vault(),
      m_World(4200.0, 3000.0),
      m_WorldPos(0.0, 0.0),
      m_Camera(m_Window),
      m_CameraPos(0.0, 0.0),
      m_CurrentHiveIndex(0),
      m_CurrentAntIndex(0)
{
    m_Window.setFramerateLimit(144);
    m_Window.setVerticalSyncEnabled(true);

    m_World.spawnHive(sf::Color::Green, sf::Vector2f(1000.0, 1000.0), 100, 1);
    m_World.spawnHive(sf::Color::Red, sf::Vector2f(2000.0, 2000.0), 100, 1);
    m_World.spawnClumpOfFood(sf::Vector2f(1000.0, 2000.0), 50, 100.0, 1000);
    m_World.spawnClumpOfFood(sf::Vector2f(2000.0, 1000.0), 50, 100.0, 1000); 
}

Program::~Program() {}

void Program::control()
{
    sf::Event event;

    while (m_Window.pollEvent(event))
    {
        m_Camera.handle(event);

        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            m_Window.close();
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            if (m_State == ProgramState::Paused)
            {
                m_State = ProgramState::Running;
            }
            else
            {
                m_State = ProgramState::Paused;
            }
        }
    }
}

void Program::paint(float scrW, float scrH)
{
    std::string state = "State: ";

    if (m_State == ProgramState::Paused)
        state += "Paused";
    else
        state += "Running";

    sf::RectangleShape side(sf::Vector2f(400.0, scrH));
    side.setFillColor(sf::Color(200, 200, 200, 255));
    side.setPosition(sf::Vector2f(0, 0));
    m_Window.draw(side);

    sf::Text textFrametime;
    textFrametime.setFont(m_Vault.font);
    textFrametime.setString("Frametime: " + std::to_string(m_FrameTimeClock.restart().asMilliseconds()) + " ms");
    textFrametime.setCharacterSize(16);
    textFrametime.setFillColor(sf::Color::Black);
    textFrametime.setPosition(sf::Vector2f(10, 10));
    m_Window.draw(textFrametime);

    sf::Text textCurrentState;
    textCurrentState.setFont(m_Vault.font);
    textCurrentState.setString(state);
    textCurrentState.setCharacterSize(16);
    textCurrentState.setFillColor(sf::Color::Black);
    textCurrentState.setPosition(sf::Vector2f(10, 30));
    m_Window.draw(textCurrentState);

    sf::Text textTicks;
    textTicks.setFont(m_Vault.font);
    textTicks.setString("Ticks: " + std::to_string(Ticks));
    textTicks.setCharacterSize(16);
    textTicks.setFillColor(sf::Color::Black);
    textTicks.setPosition(sf::Vector2f(10, 50));
    m_Window.draw(textTicks);

    sf::Text textMousePos;
    textMousePos.setFont(m_Vault.font);
    textMousePos.setString("Mouse: " + std::to_string(sf::Mouse::getPosition().x) + ", " + std::to_string(sf::Mouse::getPosition().y));
    textMousePos.setCharacterSize(16);
    textMousePos.setFillColor(sf::Color::Black);
    textMousePos.setPosition(sf::Vector2f(10, 70));
    m_Window.draw(textMousePos);

    sf::Text textCameraPos;
    textCameraPos.setFont(m_Vault.font);
    textCameraPos.setString("Camera: " + std::to_string(m_CameraPos.x) + ", " + std::to_string(m_CameraPos.y));
    textCameraPos.setCharacterSize(16);
    textCameraPos.setFillColor(sf::Color::Black);
    textCameraPos.setPosition(sf::Vector2f(10, 90));
    m_Window.draw(textCameraPos);
}

void Program::run()
{
    float scrW = (float)sf::VideoMode::getDesktopMode().width;
    float scrH = (float)sf::VideoMode::getDesktopMode().height;

    while (m_Window.isOpen())
    {
        m_Window.clear();

        control();

        if (m_State == ProgramState::Running)
        {
            m_World.update();

            Ticks++;
        }

        m_Window.setView(m_Camera.getView());
        m_World.draw(m_Window, m_WorldPos, m_Vault);

        m_Window.setView(m_Window.getDefaultView());
        paint(scrW, scrH);

        m_Window.display();
    }
}