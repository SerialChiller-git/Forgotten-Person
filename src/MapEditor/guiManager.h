#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include<SFML/Graphics.hpp>


class guiManager{
    public:

        int x = 32;
        int y = 32;
        unsigned int win_x = 512;
        unsigned int win_y = 512;

        void spriteWindow(){
            ImGui::Begin("Sprites");


            ImGui::End();
        }

        void displayGrids(sf::RenderWindow &window){
            drawGrid(window,x,y);
        }

    private:
        void drawGrid(sf::RenderWindow &window ,unsigned int x, unsigned int y){
            
            sf::VertexArray lines(sf::PrimitiveType::Lines);

            for(int i = 0; i < win_x; i++){
                lines.append({sf::Vector2f(i*x, 0), sf::Color::White});
                lines.append({sf::Vector2f(i*x, win_y), sf::Color::White});
            }

            for(int i = 0; i < win_y; i++){
                lines.append({sf::Vector2f(0, i*y), sf::Color::White});
                lines.append({sf::Vector2f(win_x, i*y), sf::Color::White});
            }

            window.draw(lines);
        }
    
};