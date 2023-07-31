#ifndef BARDITEM_HPP
#define BARDITEM_HPP

#include "../header/Item.hpp"

using namespace std;

class bardItem : public Item {
    private:
        int jamScale;
        int meditation;

    public:
        bardItem(int id, int dmgRate, int defRate, int hpRegen, int mpRegen, int r, string name, int groove, int med) :
        Item(id, dmgRate + groove, defRate, hpRegen + med, mpRegen, r, name), jamScale(groove), meditation(med) {}
        int getJamScale();
        int getMeditation();
};

#endif // BARDITEM_HPP