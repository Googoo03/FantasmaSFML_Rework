#include "../header/Boss.hpp"

using namespace std;

void Boss::selfHeal() {

    this->banditHealth = this->banditHealth + this->selfHealAbility;

}

string Boss::getBossName() {
    
    return this->bossName;

}