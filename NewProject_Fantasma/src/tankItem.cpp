#include "../header/tankItem.hpp"
using namespace std;

int tankItem::getArmor() {
    return this->armor;
}

bool tankItem::areTheyStunned() {
    if (!stun) {
        return false;
    }

    else {
        return true;
    }
}