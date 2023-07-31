#include "../header/Tank.h"
#include <iostream>

using namespace std;


double Tank::normalAttack(ostream& out)
{
    out << "you have hit the enemy!" << endl;
    this->removeMana(5);
    return this->getAttackDamage();
}

void Tank::attacked(double x, ostream& out)
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

        
double Tank::specialAttack(ostream& out)
{ 
    out << "you Just steamrolled the enemy with your special move!" << endl;
    this->removeMana(10);
    return this->getAttackDamage() + 10;
}

bool Tank::isInventoryFull()
{
    return !(this->getInventorySize() < 10);
}
void Tank::useItem(ostream& out)
{
   int idx;
   out << "which item would you like to use (1,2....)" <<endl;
   cin >> idx;

   Item* item = this->getInventoryItem(idx);
   if(this->isTankItem(item)) //checks if its a potion or fighter item
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
    cout << "that Item cannot be used by a Tank " << endl;

   }
}

bool Tank::isTankItem(Item* item)
{
   int id = item->getItemID();
   return id == 4 || id == 1;
}


void Tank::equipItem(Item*& item)

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
   else if(id == 4)
   {
    this->equipped = item;
    this->setAttackDmg( this->getAttackDamage() + item->getDamageRating());
    //cout << "It has been equipped!" << endl;
   }else{
    cout << "This doesn't belong to a Tank!" << endl;
   }
}

void Tank::UnequipItem(){

    this->equipped = nullptr;
    setAttackDmg(30);
}