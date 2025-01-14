#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include<SFML/Graphics.hpp>
#include<iostream>

struct spriteData
{
    /* data */
};



class guiManager{
    public:

        static std::vector<sf::Sprite> setSprites; // @todo: make some sort of vertexArray to load saved sprites every frame
        int x = 32;
        int y = 32;
        unsigned int win_x = 512;
        unsigned int win_y = 512;
        int tile_x = 32;
        int tile_y = 32;
        int spriteIndex = 0;
        

        char path[256];
        guiManager(){
            memset(path, 0, 256);
        }

        void spriteWindow(sf::RenderWindow &window, sf::Sprite &sprite, bool &isLoaded, sf::Texture &texture){
            ImGui::Begin("Sprites");
                ImGui::InputText("Path to Sprite" , path ,256);
                sprite.setTextureRect(sf::IntRect({spriteIndex*tile_x, 0}, {tile_x, tile_y})); // @todo: fix the y index for 2D sprites
                if(ImGui::Button("Load")){
                    if(texture.loadFromFile(path)){
                        sprite.setTexture(texture);
                        
                        isLoaded = true;
                    }
                    else{
                        std::cerr << "Texture not loaded properly \n";
                        isLoaded = false;
                    }
                }

                ImGui::InputInt("tile size", &tile_x); // Gui and logic for changing the tile size
                tile_y = tile_x;
                ImGui::InputInt("index", &spriteIndex);

            ImGui::End();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                spriteIndex++;
                std::cout << "works \n";
            }
        }

        void displayGrids(sf::RenderWindow &window){
            drawGrid(window,x,y);
        }

    private:
        void drawGrid(sf::RenderWindow &window ,unsigned int x, unsigned int y){
            
            sf::VertexArray lines(sf::PrimitiveType::Lines);

            for(int i = 0; i < win_x; i++){
                if(i*x > win_x){
                    break;
                }
                lines.append({sf::Vector2f(i*x, 0), sf::Color::White});
                lines.append({sf::Vector2f(i*x, win_y), sf::Color::White});
            }

            for(int i = 0; i < win_y; i++){
                if(i*y > win_y){
                    break;
                }
                lines.append({sf::Vector2f(0, i*y), sf::Color::White});
                lines.append({sf::Vector2f(win_x, i*y), sf::Color::White});
            }

            window.draw(lines);
        }
    
};