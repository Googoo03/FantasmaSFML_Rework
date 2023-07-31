#include "../header/FightScreen.h"
#include <iostream>

using namespace std;

bool FightScreen::fight(Character* character, Bandit* bandit, ostream& out)
{
    bool fighting = true;

    while(fighting)
    {
        char choice = ' ';
        while(choice != '1' && choice != '2' && choice != '3')
        {
            out << "-------------------------------" << endl;
            out << " (1) - NORMAL ATTACK (2) - SPECIAL ATTACK (3) - USE ITEM " << endl;
            out << "-------------------------------" << endl;
            out << "Current HP: " << character->getHealth() << " " << "Current MP: " << character->getMana();
            out << endl;
            cin >> choice;
            cout << endl;
        }

        if(choice == '1')
        {
            bandit->dealDamage(character->normalAttack(out));
            out << endl;
        }
        if(choice == '2')
        {
            bandit->dealDamage(character->specialAttack(out));
            out << endl;
        }
        if(choice == '3')
        {
            if(character->getInventorySize() > 0)
            {
                character->displayInventory();
                character->useItem(out);
            }
            else
            {
                out << "your inventory is empty!" << endl;
            }
        }
        if(bandit->getBanditHealth() > 0)
        {
            character->attacked(bandit->getDamageDone(), out);
        }
        if(character->getHealth() <= 0)
        {
            fighting = false;
            return false;
        }
        else if( bandit->getBanditHealth() <= 0)
        {
            return true;
            //out << "-------------------------------" << endl;
            //out << "YOU HAVE DEFEATED THE BANDIT" << endl;
            //out << "-------------------------------" << endl;
            fighting = false;
        }
    }
    return false;

}

void FightScreen::printFightScreen(ostream& out,Character* character, Bandit* bandit, bool& win)

{
    char choice = ' ';
    bool input = true;
    while(input)
    {
        while(choice != '1' && choice != '2')
        {
            out << "-------------------------------" << endl;
            out << "You have encountered an enemy!" << endl;
            out << "-------------------------------" << endl;
            out << "you can fight(1) or run(2)" << endl;
            out << "-------------------------------" << endl;
            cin >> choice;
        }

        if(choice == '1' || choice == '2')
        {
            input = false;
        }
    } 

    if(choice == '1')
    {
        win = this->fight(character, bandit, out);
    }
    else if(choice == '2')
    {
        out << "You have succesfully ran away from the enemy!" << endl;
    }
}

void FightScreen::printBossScreen(std::ostream& out, Character* character, Boss* bandit, std::string name,bool& win)
{
    
    bool input = true;
    char choice = ' ';
    while(input)
    {
        
        while(choice != '1' && choice != '2' && choice != '3')
        {
            out << "-------------------------------" << endl;
            out << "You are about to face " << name << "!" << endl;
            out << "-------------------------------" << endl;
            out << "Prepare to die! " << endl;
            out << "-------------------------------" << endl;
            out << "you can fight(1) or run(2)" << endl;
            out << "-------------------------------" << endl;
            cin >> choice;
        }
        
        if(choice == '1' || choice == '2')
        {
            input = false;
        }
    } 

    if(choice == '1')
    {
        win = this->bossFight(character, bandit, out);
    }
    else if(choice == '2')
    {
        out << "You have succesfully ran away from the enemy!" << endl;
    }
}

bool FightScreen::bossFight(Character* character, Boss* bandit, std::ostream& out)
{
     bool fighting = true;
    int choice = 0;
    while(fighting)
    {
        char choice = ' ';
        while(choice != '1' && choice != '2' && choice != '3')
        {
            out << "-------------------------------" << endl;
            out << " (1) - NORMAL ATTACK (2) - SPECIAL ATTACK (3) - USE ITEM " << endl;
            out << "-------------------------------" << endl;
            out << "Your current HP: " << character->getHealth() << " " << "Your current MP: " << character->getMana();
            out << endl;
            cin >> choice;
            cout << endl;
        }

        if(choice == '1')
        {
            bandit->dealDamage(character->normalAttack(out));
            out << endl;
        }
        if(choice == '2')
        {
            bandit->dealDamage(character->specialAttack(out));
            out << endl;
        }
        if(choice == '3')
        {
            if(character->getInventorySize() > 0)
            {
                character->displayInventory();
                character->useItem(out);
            }
            else
            {
                out << "your inventory is empty!" << endl;
            }
        }

        if(bandit->getBanditHealth() > 0)
        {
            bandit->selfHeal();
            out << "The Boss has regenerated Health!!" << endl;
            character->attacked(bandit->getDamageDone(), out);
        }

        if(character->getHealth() <= 0)
        {
            fighting = false;
            return false;
        }
        else if( bandit->getBanditHealth() <= 0)
        {
            return true;
            //out << "-------------------------------" << endl;
            //out << "YOU HAVE DEFEATED THE BOSS" << endl;
            //out << "-------------------------------" << endl;
            fighting = false;
        }
    }
    return false;
    
}

void FightScreen::bossWin(){
    cout << "-------------------------------" << endl;
    cout << "YOU HAVE DEFEATED THE BOSS" << endl;
    cout << "-------------------------------" << endl;
}

void FightScreen::fightWin(){
    cout << "-------------------------------" << endl;
    cout << "YOU HAVE DEFEATED THE BANDIT" << endl;
    cout << "-------------------------------" << endl;
}