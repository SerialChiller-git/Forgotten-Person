#include "calculations.h"
#include <math.h>

sf::Vector2f normalize(sf::Vector2f& source) {
    float length = std::sqrt(source.x * source.x + source.y * source.y);
    if(length != 0) {
        return sf::Vector2f(source.x/length, source.y/length);
    }
    return source;
}

bool checkCollision(Player& player, Player& player2) {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f player2Pos = player2.getPosition();

    if(playerPos.x < player2Pos.x + player2.spriteWidth - 32.0f &&
        playerPos.x + player.spriteWidth > player2Pos.x + 32.0f &&
        playerPos.y < player2Pos.y + player2.spriteHeight - 32.0f &&
        playerPos.y + player.spriteHeight > player2Pos.y + 32.0f) {
        return true;
    }
    return false;
}