#ifndef FIGHTERITEM_HPP
#define FIGHTERITEM_HPP

#include "../header/Item.hpp"

using namespace std;

class fighterItem : public Item {
    private:
        int rage; // add this val to damage and health regen
        int dexterity; //grants multiple attacks

    public:
        fighterItem(int id, int dmgRate, int defRate, int hpRegen, int mpRegen, int r, string name, int angry, int dex) : 
        Item(id, dmgRate + angry, defRate, hpRegen + angry, mpRegen, r, name), rage(angry), dexterity(dex) {}
        int getRage();
        int getDexterity();
};

#endif // FIGHTERITEM_HPP