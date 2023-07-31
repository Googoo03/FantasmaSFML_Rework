#include "../header/Item.hpp"

using namespace std;

int Item::getItemID() {
    return this->itemID;
}

int Item::getDamageRating() {
    return this->damageRating;
}

int Item::getDefenseRating() {
    return this->defenseRating;
}

int Item::getHealthRegen() {
    return this->healthRegen;
}

int Item::getRange() {
    return this->range;
}

int Item::getManaRegen() {
    return this->manaRegen;
}

string Item::getItemName() {
    return this->itemName;
}


