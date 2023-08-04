#ifndef TILEMAP_H
#define TILEMAP_H
#include "SFML/Graphics.hpp"
#include <iostream>


using namespace std;

class Tilemap : public sf::Drawable, public sf::Transformable {

public:
    
	bool load(const string& filename, sf::Vector2u tileResolution,const static int size, int* tiles, int scene);

    sf::VertexArray& getVarray() { return t_varray; }
private:
	sf::VertexArray t_varray;
	sf::Texture t_tileSet;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &t_tileSet;

        // draw the vertex array
        target.draw(t_varray, states);
    }
};

#endif
