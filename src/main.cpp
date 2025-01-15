#include<imgui.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include<iostream>
#include<thread>
#include <mutex>
#include "gameTile.h"
#include "Player.h"
#include "calculations.h"


sf::Texture playerTexture;

const int WINDOW_X = 1024;
const int WINDOW_Y = 512;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_X, WINDOW_Y}), "Forgotten Person");
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

    Player player2;
    if(!player2.loadTexture("assets/player.png")){
        std::cerr << "Texture not loaded properly \n";
    }

    map.setScale({2, 1});

    player.setFrame(1, 64, 64);
    player2.setFrame(1, 64, 64);

    player2.setPosition({900, 400});
    
    

    
    sf::Clock deltaClock;
    sf::Time deltaTime;
    std::mutex windowMutex; 

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
                case sf::Keyboard::Scancode::R:
                    player2.alive = true;
                    player2.setPosition({900, 400});
                    player.setPosition({0, 0});

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
        movement = normalize(movement);
        movement.x*= player.speed*deltaTime.asSeconds();
        movement.y*= player.speed*deltaTime.asSeconds();

        sf::Vector2f movement2 = {0.0f, 0.0f};

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
                    player2.setFrame(3, 64, 64);
                    movement2.x -= 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                    player2.setFrame(2, 64, 64);
                    movement2.x += 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
                    player2.setFrame(0, 64, 64);
                    movement2.y -= 1;
                    
                    }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
                    player2.setFrame(1, 64, 64);
                    movement2.y += 1;
                    
                 }
        movement2 = normalize(movement2);
        movement2.x*= player2.speed*deltaTime.asSeconds();
        movement2.y*= player2.speed*deltaTime.asSeconds();
        if(checkCollision(player, player2)){
            player2.alive = false;
        }
        

        player.move(movement);
        player2.move(movement2);

        sf::Vector2f playerPos = player.getPosition();
        sf::Vector2f player2Pos = player2.getPosition();

        if(playerPos.x < 0){
            player.setPosition({0, playerPos.y});
        }
        if(playerPos.x > WINDOW_X - 64){
            player.setPosition({WINDOW_X - 64, playerPos.y});
        }
        if (playerPos.y < 0){
            player.setPosition({playerPos.x, 0});
        }
        if(playerPos.y > WINDOW_Y - 64){
            player.setPosition({playerPos.x, WINDOW_Y - 64});
        }
        
        if(player2Pos.x < 0){
            player2.setPosition({0, player2Pos.y});
        }
        if(player2Pos.x > WINDOW_X - 64){
            player2.setPosition({WINDOW_X - 64, player2Pos.y});
        }
        if (player2Pos.y < 0){
            player2.setPosition({player2Pos.x, 0});
        }
        if(player2Pos.y > WINDOW_Y - 64){
            player2.setPosition({player2Pos.x, WINDOW_Y - 64});
        }
        
        

        window.clear(sf::Color::Black);
        window.draw(map);
        window.draw(player);
        window.draw(player2);
        window.display();
    }
}
