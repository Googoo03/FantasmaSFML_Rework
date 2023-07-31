#include "../header/Bard.h"
 #include <iostream>
 
 using namespace std;

 double Bard::normalAttack(ostream& out)
 {
   if(this->getMana() >= 15)
   {
      out << "you just hit the enemy with your guitar!" << endl;
      this->removeMana(15);
      return this->getMagicDamage();
   }
   else
   out << "You have run out of mana! drink a potion!" << endl;
   return 0;
 }

 double Bard::specialAttack(ostream& out)
 {
   if(this->getMana() >= 25)
   {
      out << "you played a song for the enemy which critically hurt their ears!" << endl;
      this->removeMana(25);
      return this->getMagicDamage() + 10;
   }
   else
   out << "you have run out of mana! drink a potion!" << endl;
   return 0;
 }

 void Bard::attacked(double x, ostream& out)
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

 bool Bard::isInventoryFull()
 {
   return !(this->getInventorySize() < 6);
 }

 void Bard::useItem(ostream& out)
{
   int idx;
   out << "which item would you like to use (1,2....)" <<endl;
   cin >> idx;

   Item* item = this->getInventoryItem(idx);
   if(this->isBardItem(item)) //checks if its a potion or fighter item
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
    cout << "that Item cannot be used by a Bard " << endl;

   }
 }

 bool Bard::isBardItem(Item* item)
 {
   int id = item->getItemID();
   return id == 5 || id == 1;
 }


 void Bard::equipItem(Item*& item)

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
   else if(id == 5)
   {
    this->equipped = item;
    this->setAttackDmg( this->getAttackDamage() + item->getDamageRating());
    //cout << "It has been equipped!" << endl;
   }else{
    cout << "This doesn't belong to a Bard!" << endl;
    //cout << "Press any key to continue.." << endl;
    //cin.get();
   }
 }

 void Bard::UnequipItem(){

    this->equipped = nullptr;
    setAttackDmg(30);
}