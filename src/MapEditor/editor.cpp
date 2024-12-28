#include <imgui.h>
#include <imgui-SFML.h>

#include<SFML/Graphics.hpp>
#include<cstdint> // for uint8_t
#include "guiManager.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({512, 512}), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    //======== codes for background colour ==============

    float color[3] = {0.0f, 0.0f, 0.0f};
    sf::Color bgcolor;

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
        }

        ImGui::SFML::Update(window, deltaClock.restart());

       

        ImGui::Begin("Controls");

        if(ImGui::ColorEdit3("Backgorund color", color)){
            bgcolor.r = static_cast<std::uint8_t>(color[0] * 255.0f);
            bgcolor.g = static_cast<std::uint8_t>(color[1] * 255.0f);
            bgcolor.b = static_cast<std::uint8_t>(color[2] * 255.0f);
        }
        ImGui::SliderInt("grid X", &gui.x, 1, 100);
        ImGui::SliderInt("grid Y", &gui.y, 1, 100);

        ImGui::End();

        window.clear(bgcolor);
        gui.displayGrids(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}