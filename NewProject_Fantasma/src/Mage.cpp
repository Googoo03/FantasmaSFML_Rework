#include "../header/Mage.h"
#include <iostream>

using namespace std;

double Mage::normalAttack(ostream& out)
{
    if(this->getMana() >= 10)
    {
        out << "you have hit the enemy!" << endl;
        this->removeMana(10);
        return this->getMagicDamage();
    }
    out << "you have run out of mana!" <<endl;
    return 0;
}

double Mage::specialAttack(ostream& out)
{
    if(this->getMana() >= 20)
    {
        out << "you hit the enemy with your special move!" << endl;
        this->removeMana(20);
        return this->getMagicDamage() + 10;
    }
    out << "you have run out of mana! drink a potion!" << endl;
    return 0;
 }

void Mage::attacked(double x, ostream& out)
{
    this->removeHealth(x);
    if(this->getHealth() <= 0)
    {
        out << "your character has died! game over...." << endl;
    }
    else
    {
        out << "you've been hit!" << endl;
    }
}

bool Mage::isInventoryFull()
{
    return !(this->getInventorySize() < 4);
}
void Mage::useItem(ostream& out)
{   
   int idx;
   out << "which item would you like to use (1,2....)" <<endl;
   cin >> idx;

   Item* item = this->getInventoryItem(idx);
   if(this->isMageItem(item)) //checks if its a potion or fighter item
   {  


   
    
    if(item->getItemID() == 1){ //destroys if potion
        this->addHealth(item->getHealthRegen());
        
        this->removeItem(idx);
        delete item;

    }else{
        this->equipItem(item);
        usingItem = true;
    }
    

   }else{
    cout << "that Item cannot be used by a Mage " << endl;

   }
}

bool Mage::isMageItem(Item* item)
{
   int id = item->getItemID();
   return id == 3 || id == 1;
}


void Mage::equipItem(Item*& item)

{
    int id = item->getItemID();
   if(id == 1)
   {


    int i = 0;
    for(i = 0; i < this->getInventorySize(); ++i){
        if(this->getInventoryItem(i) == item) break;
    }
        
      this->addHealth( item->getHealthRegen());
      delete item;
      this->removeItem(i);
      
      

   }
   else if(id == 3)
   {
    this->equipped = item;
    this->setAttackDmg( this->getAttackDamage() + item->getDamageRating());
    //cout << "It has been equipped!" << endl;
   }else{
    cout << "This doesn't belong to a Mage!" << endl;
   }
}

void Mage::UnequipItem(){

    this->equipped = nullptr;
    setAttackDmg(30);
}