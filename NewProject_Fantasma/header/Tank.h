#ifndef TANK_H
#define TANK_H

#include "../header/Character.h"
#include <iostream>


class Tank: public Character {
    private:
    bool usingItem;
    bool isTankItem(Item* item);

    void equipItem(Item*& item);
    
    public:
    void UnequipItem();
    
    Tank() : usingItem{false}, Character(200, 60, 30, 20, 10, 4, 200,0) {}


    void attacked(double x, std::ostream& out);
    double normalAttack(std::ostream& out); 
    double specialAttack(std::ostream& out); 
    bool isInventoryFull();
    void useItem(std::ostream& out);
    

};
#endif