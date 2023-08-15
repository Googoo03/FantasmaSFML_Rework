#include "../header/Character.h"
#include <iostream>
using namespace std;

Character::~Character(){
    for(int i = inventory.size()-1; i >= 0; --i){
        delete inventory.at(i);
    }
}

void Character::setCharacterPosition(int tile, int mapSize) {
    sf::Vector2i pos = sf::Vector2i( (tile%16) * 64, (tile /16) * 64);
    characterPosition = pos;
}

void Character::setNewTile(int tile) { nextTile = tile; }

void Character::interpolatePosition() {
    if (oldPosition == sf::Vector2i(-1, -1)) oldPosition = characterPosition;

    sf::Vector2i destination = sf::Vector2i(((nextTile % 16) * 64), ((nextTile / 16) * 64));

    if (characterPosition == destination) { //finished moving
        characterTileNum = nextTile;
        nextTile = -1;
        interpolationFactor = 0;
        oldPosition = sf::Vector2i(-1, -1);
        canMove = true;
        return;
    }

    
    characterPosition.x = oldPosition.x + (interpolationFactor * (destination.x - oldPosition.x));
    characterPosition.y = oldPosition.y + (interpolationFactor * (destination.y - oldPosition.y));

    interpolationFactor += 0.01; //CHANGE LATER
}

void Character::setCanMove(bool set) { canMove = set; }
void Character::setTilePos(int tile) { characterTileNum = tile; }

void Character::updateCharacter() {
    uint16_t characterSpriteIndex = ((characterPosition.x / 16) + (characterPosition.y / 16)) % 3;

    characterSprite.setPosition(characterPosition.x - (characterPosition.x % 8), characterPosition.y - (characterPosition.y % 8));
    characterSprite.setTexture(textureArray[characterSpriteIndex]);
}

/*void Character::enteredStructureCheck(int p) {

}*/

void Character::setCharacterDirection(bool right) {
    if (right) {
        characterSprite.setTextureRect(sf::IntRect(0, 0, 8, 8));
    }
    else {
        characterSprite.setTextureRect(sf::IntRect(8, 0, -8, 8));
    }
}

void Character::removeHealth(double x)
{
    if(x > 0)
    {
        healthPoints -= x;
    }
}
void Character::removeMana(double x)
{
    if(x > 0)
    {
        manaPoints -= x;
    }
}

void Character::addItem(Item* item)
{
    if(inventory.size() < carryCapacity)
    {
        inventory.push_back(item);
    }
    else
    {
        cout << "your inventory is full!" << endl;
    }
}

double Character::getHealth()
{
    return healthPoints;
}

double Character::getMana()
{
    return manaPoints;
}

void Character::displayInventory()
{
    string equippedItemName = "None";
    if(this->getEquipped() != nullptr){
        equippedItemName = this->getEquipped()->getItemName();
    }
    cout << "-----------------CHARACTER-----------------" << endl;
    cout << "Health:" << this->getHealth() << endl;
    cout << "Mana:" << this->getMana() << endl;
    cout << "Equipped: " << equippedItemName << endl;
    cout << "-----------------INVENTORY-----------------" << endl;

    int i = 1;
    for (/*auto x: inventory*/ i = 0; i< this->inventory.size();++i)
    {
        Item* x = this->inventory.at(i);
        cout << i+1 << " - " << x->getItemName() << " " <<endl;
        //i ++;
    }

    cout << "-------------------------------------------" << endl;

    
}

double Character::getAttackDamage()
{
    return this->attackDamage;
}
        

void Character::setAttackDmg(double x)
{
    this->attackDamage = x; //changed
}

double Character::getMagicDamage()
{
    return this->magicDamage;
}

int Character::getInventorySize()
{
    return inventory.size();
}

Item*& Character::getInventoryItem(int idx)
{
    return inventory[idx];
} 

void Character::removeItem(int idx)
{
    inventory.erase(inventory.begin() + idx);
}

void Character::addHealth(double buff)
{
    healthPoints += buff;
}

void Character::setMagicDmg(double dmg)
{
    magicDamage = dmg; //changed
}

int Character::getId()
{
    return id; 
}
