#include "../src/FightScreen.cpp"
#include "../src/Bandit.cpp"
#include "../src/Fighter.cpp"
#include "../src/Character.cpp"
#include "../src/Item.cpp"
#include "../src/Boss.cpp"
#include "../src/Bard.cpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
   
   //Fighter* fighter = new Fighter;
    //Bandit* bandit = new Bandit(100, 10);
    FightScreen fightScreen;

    //fightScreen.printFightScreen(cout, fighter, bandit);
    

    Bard* bard = new Bard;
    Boss* boss = new Boss(150,30,"THE BOSS", 20);
    bool win = false;

    fightScreen.printBossScreen(cout, bard, boss, boss->getBossName(), win);

    return 0;
}