#ifndef BANDIT_HPP
#define BANDIT_HPP
#include "SFML/Graphics.hpp"

using namespace std;

class Bandit {
    private:
        double banditAttack;
        sf::Texture textureArray[3];
        uint16_t textureSize;
        sf::Vector2u position = sf::Vector2u(0,0);
        sf::Sprite sprite;
    public:
        double banditHealth;
        Bandit(double bh, double ba, int TextureX, int TextureY, sf::Vector2u pos) : banditHealth(bh), banditAttack(ba),textureSize(8),position(pos) {
            for (int i = 0; i < 3; ++i) {
                textureArray[i].loadFromFile("Tilemap.png", sf::IntRect(TextureX, TextureY + (textureSize * i), textureSize, textureSize));
                
            }
            sprite.setTexture(textureArray[1]);
            sprite.setPosition(pos.x, pos.y);
            sprite.setScale(8, 8);
        }


        sf::Texture& getTexture(int index) { return textureArray[index]; }
        sf::Sprite& getSprite() { return sprite; }
        double getDamageDone();
        void dealDamage(double d);
        double getBanditHealth();

};

#endif //BANDIT_HPP
