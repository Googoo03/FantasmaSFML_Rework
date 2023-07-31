#ifndef MAGEITEM_HPP
#define MAGEITEM_HPP

#include "../header/Item.hpp"

using namespace std;

class mageItem : public Item {
    private:
        int magicDamage;
        int selfHeal;

    public:
        mageItem(int id, int dmgRate, int defRate, int hpRegen, int mpRegen, int r, string name, int magic, int xtraHealth) :
        Item(id, dmgRate + magic, defRate, hpRegen + xtraHealth, mpRegen, r, name), magicDamage(magic), selfHeal(xtraHealth) {}
        int getMagicDamage();
        int getSelfHeal(); 
};

#endif // MAGEITEM_HPP
