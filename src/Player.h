#pragma once
#include<SFML/Graphics.hpp>
#include<filesystem>

class Player : public sf::Drawable, public sf::Transformable{
    public:
        
        int health;
        sf::Texture texture;
        int spriteWidth;
        int spriteHeight;
        sf::Sprite sprite;
        int speed;
        bool alive = true;
        Player(): sprite(texture){
            speed = 200;
            health = 100;
            sprite.setPosition({0, 0});
            sprite.setScale({1, 1});
            
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
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            states.transform *= getTransform();
            if(alive){
                target.draw(sprite, states);
            }
        }

};