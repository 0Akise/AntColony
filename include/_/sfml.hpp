#pragma once

#include <SFML/Graphics.hpp>

#include <util.hpp>

#include <cmath> // std::cos, std::sin

namespace sf
{
    class RoundedRectangleShape : public sf::Shape
    {
    private:
        Vector2f m_Size;
        float m_Radius;
        unsigned int m_CornerPointCount;

    public:
        explicit RoundedRectangleShape(const Vector2f &size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0);

        const Vector2f &getSize() const { return m_Size; }
        float getCornersRadius() const { return m_Radius; }
        virtual std::size_t getPointCount() const;
        virtual sf::Vector2f getPoint(std::size_t index) const;
        void setSize(const Vector2f &size);
        void setCornersRadius(float radius);
        void setCornerPointCount(unsigned int count);
    };
}

namespace sf
{
    RoundedRectangleShape::RoundedRectangleShape(const Vector2f &size, float radius, unsigned int cornerPointCount)
    {
        m_Size = size;
        m_Radius = radius;
        m_CornerPointCount = cornerPointCount;

        update();
    }

    std::size_t RoundedRectangleShape::getPointCount() const
    {
        return m_CornerPointCount * 4;
    }

    Vector2f RoundedRectangleShape::getPoint(std::size_t index) const
    {
        if (index >= m_CornerPointCount * 4)
            return Vector2f(0, 0);

        float deltaAngle = 90.0f / (m_CornerPointCount - 1);
        sf::Vector2f center;
        unsigned int centerIndex = (unsigned int)(index / m_CornerPointCount);

        switch (centerIndex)
        {
        case 0:
            center.x = m_Size.x - m_Radius;
            center.y = m_Radius;
            break;
        case 1:
            center.x = m_Radius;
            center.y = m_Radius;
            break;
        case 2:
            center.x = m_Radius;
            center.y = m_Size.y - m_Radius;
            break;
        case 3:
            center.x = m_Size.x - m_Radius;
            center.y = m_Size.y - m_Radius;
            break;
        }

        return Vector2f(m_Radius * std::cos(deltaAngle * (index - centerIndex) * R_01::MathUtil::PI / 180) + center.x,
                        -m_Radius * std::sin(deltaAngle * (index - centerIndex) * R_01::MathUtil::PI / 180) + center.y);
    }

    void RoundedRectangleShape::setSize(const Vector2f &size)
    {
        m_Size = size;

        update();
    }

    void RoundedRectangleShape::setCornersRadius(float radius)
    {
        m_Radius = radius;

        update();
    }

    void RoundedRectangleShape::setCornerPointCount(unsigned int count)
    {
        m_CornerPointCount = count;

        update();
    }
}