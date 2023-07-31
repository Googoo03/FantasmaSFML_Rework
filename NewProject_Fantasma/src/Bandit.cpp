#include "../header/Bandit.hpp"
#include "iostream"
using namespace std;

double Bandit::getDamageDone() {
    return 10.0;
}

void Bandit::dealDamage(double d) {
    
    this->banditHealth = this->banditHealth - d;
    /*
    if (banditHealth <= 0) {
        cout << " The enemy has been slain!" << endl;
    } */

}

double Bandit::getBanditHealth() {
    return banditHealth;
}