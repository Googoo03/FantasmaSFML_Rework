#ifndef TANKITEM_HPP
#define TANKITEM_HPP
#include "../header/Item.hpp"

using namespace std;

class tankItem : public Item {
    private:
        int armor;
        bool stun;

    public:
        tankItem(int id, int dmgRate, int defRate, int hpRegen, int mpRegen, int r, string name, int chonk, bool boom) :
        Item(id, dmgRate, defRate + chonk, hpRegen + chonk, mpRegen, r, name), armor(chonk), stun(true) {}
        int getArmor();
        bool areTheyStunned();
};

#endif // TANKITEM_HPP