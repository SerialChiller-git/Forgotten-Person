#include "gameTile.h"

bool gameTile::load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height){
    if(!m_tileset.loadFromFile(tileset)){
        return false;
    }
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(height*width*6);

    
    for(unsigned int i = 0; i < width; i++){
        for(unsigned int j = 0; j < height; j++){
            const int tileNumber = tiles[i + j*width];
            const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            sf::Vertex* triangles = &m_vertices[(i+j*width)*6];

            // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y); 
        }
    }
    return true;
}

void gameTile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform *= getTransform();
        states.texture = &m_tileset;

        target.draw(m_vertices, states);
}

