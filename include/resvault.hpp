#pragma once

#include <SFML/Graphics.hpp>

struct ResourceVault
{
    sf::Font font;
    sf::Texture antTexture;

    ResourceVault()
    {
        if (!font.loadFromFile("res/font.ttf"))
            throw std::runtime_error("Failed to load font");
        
        if (!antTexture.loadFromFile("res/ant.png"))
            throw std::runtime_error("Failed to load ant texture");

        antTexture.setSmooth(true);
    }
};