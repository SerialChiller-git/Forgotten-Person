#include<imgui.h>
#include <SFML/Graphics.hpp>
#include<iostream>
#include "gameTile.h"
#include "Player.h"
#include "calculations.h"

sf::Texture playerTexture;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1024, 512}), "Forgotten Person");
    window.setFramerateLimit(75);
    
  constexpr std::array level = {
    0, 1, 2, 3, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4,
    0, 1, 0, 0, 3, 0, 4, 4, 4, 0, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 4, 4, 4, 0, 0, 0, 1, 1, 1, 3, 0, 0,
    0, 0, 1, 0, 4, 0, 3, 3, 0, 0, 1, 1, 1, 1, 3, 0,
    3, 0, 1, 0, 4, 0, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 0, 4, 3, 3, 3, 0, 0, 0, 0, 1, 10, 11, 1,
    0, 1, 2, 3, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4,
    0, 1, 0, 0, 3, 0, 4, 4, 4, 0, 1, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 4, 4, 4, 0, 0, 0, 1, 1, 1, 3, 0, 0,
    0, 0, 1, 0, 4, 0, 3, 3, 0, 0, 1, 1, 1, 1, 3, 0,
    3, 0, 1, 0, 4, 0, 3, 3, 3, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 0, 4, 3, 3, 3, 0, 0, 0, 0, 1, 10, 11, 1
    };


    gameTile map;
    if (!map.load("assets/levelSet.png", {32, 32}, level.data(), 16, 16))
        return -1;

    Player player;
    if(!player.loadTexture("assets/player.png")){
        std::cerr << "Texture not loaded properly \n";
    }

    map.setScale({2, 1});

    player.setFrame(1, 64, 64);
    
    

    
    sf::Clock deltaClock;
    sf::Time deltaTime;
    while (window.isOpen())
    {   
        deltaTime = deltaClock.restart();
        sf::Vector2f movement = {0.0f, 0.0f};
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
                
                default:
                    break;
                }
            }
        }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                    player.setFrame(3, 64, 64);
                    movement.x -= 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                    player.setFrame(2, 64, 64);
                    movement.x += 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                    player.setFrame(0, 64, 64);
                    movement.y -= 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                    player.setFrame(1, 64, 64);
                    movement.y += 1;
                    
                 }
        std::cout << movement.x << " " << movement.y << "\n";
        movement = normalize(movement);
        movement.x*= player.speed*deltaTime.asSeconds();
        movement.y*= player.speed*deltaTime.asSeconds();

        player.move(movement);
        

        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(player);
        window.display();
    }
}
