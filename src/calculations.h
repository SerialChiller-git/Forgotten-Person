#include <SFML/Graphics.hpp>
#include<math.h>

sf::Vector2f normalize(sf::Vector2f& source){
    float length = std::sqrt(source.x * source.x + source.y * source.y);
    if(length != 0){
        return sf::Vector2f(source.x/length, source.y/length);
    }
    else{
        return source;
    }
}