#pragma once
#include<SFML/Graphics.hpp>
#include<filesystem>
#include<iostream>
#include<string>

class Player : public sf::Drawable, public sf::Transformable{
    public:
        
        int health;
        sf::Texture texture;
        int spriteWidth;
        int spriteHeight;
        sf::Sprite sprite;
        int speed;
        bool alive = true;
        sf::Font font;
        sf::Text text;
        bool notChaser; 
        bool showText = true;
        Player(): sprite(texture) , text(font){
            speed = 200;
            health = 100;
            sprite.setPosition({0, 0});
            sprite.setScale({1, 1});
            if(!font.openFromFile("assets/Pixel Game.otf")){
                std::cerr << "Font not loaded properly \n";
            }
            text.setFont(font);
            text.setStyle(sf::Text::Bold);
            text.setCharacterSize(30);
            text.setPosition(sprite.getPosition());
        }

        bool loadTexture(const std::filesystem::path& path){
            if(!texture.loadFromFile(path)){
                return false;
            }
            sprite.setTexture(texture);
            return true;
        }

        void setFrame(int i, int spriteWidth = 64, int spriteHeight = 64){
            this->spriteWidth = spriteWidth;
            this->spriteHeight = spriteHeight;
            sprite.setTextureRect(sf::IntRect({i*spriteWidth, 0} , {spriteWidth, spriteHeight}));
        }

        void takeDamage(int damage){
            health -= damage;
        }

        void heal(int heal){
            health += heal;
        }
        void setTextColor(){
            if(this->notChaser == false){
                text.setString("Chaser");
                text.setFillColor(sf::Color::Red);
            }
            else{
                text.setString("Runner");
                text.setFillColor(sf::Color::Blue);
            }
        }
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            states.transform *= getTransform();
            if(alive){
                target.draw(sprite, states);
                if(showText){
                    target.draw(text, states);
                }
            }
        }

        

};