#ifndef FIGHTER_H
#define FIGHTER_H

#include "../header/Character.h"
#include "SFML/Graphics.hpp"
#include "iostream"

class Fighter: public Character {
    private:

        bool usingItem;
        bool isFighterItem(Item* item);
        void equipItem(Item*& item);
        //sf::Texture texture;
   


    public:
        void UnequipItem();

        Fighter() : usingItem(false), Character{180, 80 , 50, 30, 8, 2, 176,0} {}

        void loadTexture();
        double normalAttack(std::ostream& out);
        double specialAttack(std::ostream& out);
        void attacked(double x, std::ostream& out);
        bool isInventoryFull();
        void useItem(std::ostream& out);
        

        

};


#endif
