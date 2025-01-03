#include <imgui.h>
#include <imgui-SFML.h>

#include<SFML/Graphics.hpp>
#include<cstdint> // for uint8_t
#include "guiManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "TileMap Editor");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    //======== variables to modify the Gui ==============

    float color[3] = {0.0f, 0.0f, 0.0f};
    sf::Color bgcolor;
    int inputValue = 32;
    sf::Texture defaultTexture(sf::Vector2u{200,200});
    sf::Sprite sprite(defaultTexture);
    bool isLoaded = false;
    bool isDragging = false;
    //============== objects ==========================

    guiManager gui;


    //========= main loop ==============================
    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if(sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                    isDragging = true;
                }
            }
            else{
                isDragging = false;
            }

            if(event->is<sf::Event::MouseMoved>()){
                if(isDragging){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f spriteSize = static_cast<sf::Vector2f>(sprite.getTexture().getSize());
                    sprite.setPosition(static_cast<sf::Vector2f>(mousePos) - spriteSize/4.0f);
                }
            }

        }

        ImGui::SFML::Update(window, deltaClock.restart());

       
        // Start of Gui , will move it to a method later
        ImGui::Begin("Controls");

        if(ImGui::ColorEdit3("Backgorund color", color)){
            bgcolor.r = static_cast<std::uint8_t>(color[0] * 255.0f);
            bgcolor.g = static_cast<std::uint8_t>(color[1] * 255.0f);
            bgcolor.b = static_cast<std::uint8_t>(color[2] * 255.0f);
        }
        ImGui::SliderInt("grid X", &gui.x, 1, 128);
        ImGui::SliderInt("grid Y", &gui.y, 1, 128);
        if(ImGui::InputInt("Square val (x,y)" , &inputValue)){
            gui.x = inputValue;
            gui.y = inputValue;
        }
        ImGui::End();
        
        gui.spriteWindow(window, sprite, isLoaded, defaultTexture);
        window.clear(bgcolor);   // Set everything that I want to see below this except the ImGui
        
        if(isLoaded){
            window.draw(sprite);
        }

        
        gui.displayGrids(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}