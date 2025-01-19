#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

// Function declarations only
sf::Vector2f normalize(sf::Vector2f& source);
bool checkCollision(Player& player, Player& player2);