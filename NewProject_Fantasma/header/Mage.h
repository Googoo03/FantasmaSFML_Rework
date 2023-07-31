#ifndef MAGE_H
#define MAGE_H

#include "../header/Character.h"
#include <iostream>

class Mage : public Character {
    
    private:
    bool usingItem;
    bool isMageItem(Item* item);

    void equipItem(Item*& item);
    

    public:
    void UnequipItem();

    Mage() : usingItem{false}, Character(100, 150, 30, 45, 4, 3, 192, 0) {}
    double normalAttack(std::ostream& out);
    double specialAttack(std:: ostream& out);
    void attacked(double x, std::ostream& out);
    bool isInventoryFull();
    void useItem(std::ostream& out);


};


#endif 