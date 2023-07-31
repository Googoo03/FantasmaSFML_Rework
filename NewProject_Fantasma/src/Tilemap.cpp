#include "../header/Tilemap.h"

bool Tilemap::load(const string& filename, sf::Vector2u tileResolution, int* tiles, int size, int scene) {
	
	if (!t_tileSet.loadFromFile(filename)) return false;

	t_varray.setPrimitiveType(sf::Quads);
	t_varray.resize(size * size * 4);

    for (uint16_t i = 0; i < size; ++i)
        for (uint16_t j = 0; j < size; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * size];

             //////////ADD CASES FOR DIFFERENT MARCHING SQUARES
            if (tileNumber == 0) {
                if (tiles[(i)+((j + 1) * size)] >0) tileNumber += 1; //bottom
                if (tiles[(i - 1) + (j * size)] >0) tileNumber += 2; //left
                if (tiles[(i + 1) + (j * size)] >0) tileNumber += 4; //right
                if (tiles[(i) + ((j-1) * size)] >0) tileNumber += 8; //top
            }
            
            // find its position in the tileset texture
            int tu = tileNumber % (t_tileSet.getSize().x / tileResolution.x);
            int tv = (tileNumber / (t_tileSet.getSize().x / tileResolution.x))+ scene;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &t_varray[(i + j * size) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileResolution.x, j * tileResolution.y);
            quad[1].position = sf::Vector2f((i + 1) * tileResolution.x, j * tileResolution.y);
            quad[2].position = sf::Vector2f((i + 1) * tileResolution.x, (j + 1) * tileResolution.y);
            quad[3].position = sf::Vector2f(i * tileResolution.x, (j + 1) * tileResolution.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileResolution.x, tv * tileResolution.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileResolution.x, tv * tileResolution.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileResolution.x, (tv + 1) * tileResolution.y);
            quad[3].texCoords = sf::Vector2f(tu * tileResolution.x, (tv + 1) * tileResolution.y);
        }

    return true;
}