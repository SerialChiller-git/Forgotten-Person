#include<imgui.h>
#include <SFML/Graphics.hpp>
#include<iostream>
#include "gameTile.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "Forgotten Person");
    window.setFramerateLimit(75);
    
    constexpr std::array level = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    gameTile map;
    if (!map.load("assets/tileset-grassland-grass.png", {32, 32}, level.data(), 16, 8))
        return -1;


    while (window.isOpen())
    {   
        while (const std::optional event = window.pollEvent())
        {
            if(event ->is<sf::Event::Closed>()){
                window.close();
            }
            else if(const auto* keypressed = event->getIf<sf::Event::KeyPressed>()){
                switch (keypressed->scancode)
                {
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Scancode::A:
                    break;
                default:
                    break;
                }
            }
            
        }

        window.clear(sf::Color::Black);
        window.draw(map);
        window.display();
    }
}
