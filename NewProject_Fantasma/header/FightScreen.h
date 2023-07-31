#ifndef FIGHTSCREEN_H
#define FIGHTSCREEN_H

#include "../header/Character.h"
#include "../header/Bandit.hpp"
#include "../header/Boss.hpp"
#include <iostream>

class FightScreen {
    private:

    public:
    bool fight(Character* character, Bandit* bandit, std::ostream& out);
    void printFightScreen(std::ostream& out, Character* character, Bandit* bandit,bool& win);
    void printBossScreen(std::ostream& out, Character* character, Boss* bandit, std::string name,bool& win);
    bool bossFight(Character* character, Boss* bandit, std::ostream& out);
    void bossWin();
    void fightWin();
};

#endif