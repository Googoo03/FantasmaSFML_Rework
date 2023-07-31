#ifndef BARD_H 
#define BARD_H

#include "../header/Character.h"
#include <iostream>

class Bard : public Character {
    private:
    bool usingItem;
    bool isBardItem(Item* item);

    void equipItem(Item*& item);

    
    
    public:
        void UnequipItem();

    Bard() : usingItem{false}, Character(150, 120, 30, 38,6, 1, 184, 0) {}
    double normalAttack(std::ostream& out);
    double specialAttack(std::ostream& out);
    void attacked(double x, std::ostream& out);
    bool isInventoryFull();
    void useItem(std::ostream& out);

};









#endif
