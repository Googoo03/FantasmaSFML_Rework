#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

using namespace std;

class Item {
    private:
      int itemID; // 1-4 = fighter, 5-8 mage, 9-12 tank, 13-16 bard
      int damageRating;
      int defenseRating;
      int healthRegen;
      int manaRegen;
      int range;
      string itemName; 
    
    public:
      //Item();
      Item(int id, int dmgRate, int defRate, int hpRegen, int mpRegen, int r, string name) : itemID(id), 
      damageRating(dmgRate), defenseRating(defRate), healthRegen(hpRegen), manaRegen(mpRegen), range(r), itemName(name) {}
      int getItemID();
      int getDamageRating();
      int getDefenseRating();
      int getHealthRegen();
      int getManaRegen();
      int getRange();
      string getItemName();
};

#endif // ITEM_HPP
//idea to use item id as a way to tell which item belongs to which type of character