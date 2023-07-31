#include "../header/Fighter.h"
#include <iostream>

using namespace std;



double Fighter::normalAttack(ostream& out)
{
    if(this->getMana() >= 10)
    {
        out << "you have hit the enemy!" << endl;
        this->removeMana(10);
        return this->getAttackDamage();
    }
    out << "you have run out of mana!" << endl;
    return 0;
}

double Fighter::specialAttack(ostream& out)
{
    if(this->getMana() >= 15)
    {
        out << "you hit the enmy with your special move!" << endl;
        this->removeMana(15);
        return this->getAttackDamage() +10;
    }
    out << "you have run out of mana!" <<endl;
    return 0;
}

void Fighter::attacked(double x, ostream& out)
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

bool Fighter::isInventoryFull()
{
    return !(this->getInventorySize() < 8 );
}

void Fighter::useItem(ostream& out)
{
   int idx;
   out << "which item would you like to use (1,2....)" <<endl;
   cin >> idx;

   Item* item = this->getInventoryItem(idx);
   if(this->isFighterItem(item)) //checks if its a potion or fighter item
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
    cout << "that Item cannot be used by a Fighter " << endl;
   }
   
}

bool Fighter::isFighterItem(Item* item)
{
    int id = item->getItemID();
   return id == 2 || id == 1;
}


void Fighter::equipItem(Item*& item)

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
   else if(id == 2)
   {
    this->equipped = item;
    this->setAttackDmg( this->getAttackDamage() + item->getDamageRating());
    //cout << "It has been equipped!" << endl;
   }else{
    cout << "This doesn't belong to a Fighter!" << endl;
   }
}

void Fighter::UnequipItem(){

    this->equipped = nullptr;
    setAttackDmg(50);
}