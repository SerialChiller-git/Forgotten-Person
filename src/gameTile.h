#pragma once
#include<SFML/Graphics.hpp>
#include<filesystem>


class gameTile: public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

