#pragma once

#include <ui/window.hpp>
#include <ui/button.hpp>

#include <vector> // std::vector

namespace R_01
{
    class R_UI
    {
    private:
        struct M
        {
            std::vector<R_Window> _Windows;
            std::vector<R_Button> _Buttons;
        } m;

        explicit R_UI(M m) : m(std::move(m)) {}

    public:
        static R_UI create();

        void process(sf::RenderWindow &window);
    };
}

namespace R_01
{
    R_UI R_UI::create()
    {
        return R_UI(M{
            ._Windows = std::vector<R_Window>(),
            ._Buttons = std::vector<R_Button>()});
    }

    void R_UI::process(sf::RenderWindow &window)
    {
    }
}