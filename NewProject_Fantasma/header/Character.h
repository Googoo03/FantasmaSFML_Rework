#ifndef CHARACTER_H
#define CHARACTER_H

#include "../header/Item.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

#include <iostream>
#include <stack>

class Character{
    protected:
        Item* equipped;
    private:
        

        int id;
        double healthPoints;
        double manaPoints;
        double attackDamage;
        double magicDamage;
        std::vector<Item*> inventory;
        int carryCapacity;
        sf::Texture textureArray[3];
        uint16_t textureSize;
        std::stack<int> positionStack;

        sf::Sprite characterSprite;
        sf::Vector2i characterPosition;
        sf::Vector2i oldPosition;
        //sf::Vector2i newPosition;
        uint16_t characterSpeed;

        int characterTileNum;
        int nextTile;
        double interpolationFactor;

        bool canMove;
        int direction; //0 is nothing, 1 right, 2 up, 3 left, 4 down
        vector<int> walkableTiles = {16,20};
    public:

        virtual void UnequipItem() = 0;
        Item*& getEquipped(){return equipped;}
        virtual void equipItem(Item*& item) = 0;
        
        Character(double hp, double mp, double attackDmg, double magicDmg, int carryCapacity, int id, int TextureX, int TextureY) : healthPoints(hp), manaPoints(mp),attackDamage(attackDmg), magicDamage(magicDmg), carryCapacity(carryCapacity), id(id), textureSize(8), equipped(nullptr), nextTile(-1) {
            for (int i = 0; i < 3; ++i) {
                textureArray[i].loadFromFile("Tilemap.png", sf::IntRect(TextureX, TextureY+(textureSize*i), textureSize, textureSize));
            }

            characterPosition = sf::Vector2i(512, 64);
            characterTileNum = ((64/64)*16)+(512/64);
            characterSprite.setTexture(textureArray[1]);
            characterSprite.setScale(8, 8);
            characterSpeed = 1;

            interpolationFactor = 0;
            oldPosition = sf::Vector2i(-1, -1);

            canMove = true;
            direction = 0;
        }
        ~Character();

        void positionStackPush(int tile) { positionStack.push(tile); }
        int positionStackPop() { 
            int newTile = positionStack.top();
            positionStack.pop();
            return newTile;
        }
        sf::Texture& getTexture(int index) { return textureArray[index]; }
        void setCharacterPosition(int, int);
        sf::Vector2i getCharacterPosition() { return characterPosition; }
        void updateCharacter();
        void setCharacterDirection(bool); //false- 0 is left : 1 is right
        uint16_t getCharacterSpeed() { return characterSpeed; }
        sf::Sprite& getCharacterSprite() { return characterSprite; }

        void interpolatePosition();
        
        //void enteredStructureCheck(int playerTile);

        vector<int>& getWalkableTiles() { return walkableTiles; }

        bool getCanMove() { return canMove; }
        void setCanMove(bool set);

        int getTilePos() { return characterTileNum; }
        void setTilePos(int tile);

        void setNewTile(int tile);

        void addItem(Item* item);
        void removeHealth(double x);
        void removeMana(double x);
        virtual double normalAttack(std::ostream& out) = 0;
        virtual double specialAttack(std::ostream& out) = 0;
        virtual void attacked(double x, std::ostream& out) = 0;
        double getHealth();
        double getMana();
        void displayInventory();
        virtual void useItem(std::ostream& out) = 0;
        double getAttackDamage();
        void setAttackDmg(double x);
        double getMagicDamage();
        virtual bool isInventoryFull() = 0;
        int getInventorySize();
        //bool isInventoryFull(){return inventory.size() >= carryCapacity;}

        Item*& getInventoryItem(int idx);
        void removeItem(int idx);
        void addHealth(double buff);
        void setMagicDmg(double dmg);
        int getId();
    
        

        
};

#endif
