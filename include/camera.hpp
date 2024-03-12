#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
private:
    sf::RenderWindow &m_Window;
    sf::View m_View;

    bool m_IsDragging;
    sf::Vector2i m_LastMousePos;

public:
    Camera(sf::RenderWindow &m_Window);
    ~Camera();

    sf::View getView() const;

    void zoom(float factor);
    void handle(const sf::Event &event);
    void update();
};

Camera::Camera(sf::RenderWindow &window)
    : m_Window(window),
      m_View(window.getDefaultView()),
      m_IsDragging(false),
      m_LastMousePos(0, 0)
{
}

Camera::~Camera() {}

sf::View Camera::getView() const
{
    return m_View;
}

void Camera::zoom(float factor)
{
    m_View.zoom(factor);
    m_Window.setView(m_View);
}

void Camera::handle(const sf::Event &event)
{
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.delta > 0)
            zoom(0.9f);
        else
            zoom(1.1f);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_IsDragging = true;
            m_LastMousePos = sf::Mouse::getPosition(m_Window);
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            m_IsDragging = false;
        }
    }

    if ((event.type == sf::Event::MouseMoved) && (m_IsDragging))
    {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
        const sf::Vector2f deltaPos = static_cast<sf::Vector2f>(m_LastMousePos - mousePos);

        m_View.move(deltaPos * m_View.getSize().x / (float)m_Window.getSize().x);
        m_LastMousePos = mousePos;

        m_Window.setView(m_View);
    }
}

void Camera::update() {}