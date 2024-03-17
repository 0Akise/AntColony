#include <program.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Ant Colony v0.2", sf::Style::None);
    R_01::Program program = R_01::Program::Create(window);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    program.Run(window);

    return 0;
}