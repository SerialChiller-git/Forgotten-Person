#include <imgui.h>
#include <imgui-SFML.h>

#include<SFML/Graphics.hpp>
#include<cstdint> // for uint8_t




int main() {
    sf::RenderWindow window(sf::VideoMode({600, 800}), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    std::vector<sf::Shape*> kek;
    
    sf::CircleShape* circle = new sf::CircleShape(50.0f);
    circle->setFillColor(sf::Color(0,255,0));
    kek.push_back(circle);
    delete circle;
    //======== codes for background colour ==============

    float color[3] = {0.0f, 0.0f, 0.0f};
    sf::Color bgcolor;


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


        ImGui::Begin("Hello, world!");

        if(ImGui::ColorEdit3("Backgorund color", color)){
            bgcolor.r = static_cast<std::uint8_t>(color[0] * 255.0f);
            bgcolor.g = static_cast<std::uint8_t>(color[1] * 255.0f);
            bgcolor.b = static_cast<std::uint8_t>(color[2] * 255.0f);
        }

        ImGui::End();

        window.clear(bgcolor);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}