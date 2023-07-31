#include "../header/Character.h"
#include <iostream>
using namespace std;

Character::~Character(){
    for(int i = inventory.size()-1; i >= 0; --i){
        delete inventory.at(i);
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
