#include "../header/Town.h"
#include "../header/Item.hpp"
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

Town::Town(int x, int y, int seed) : Location{x, y, seed} {}

Town::~Town(){
    for(int i = shopItems.size()-1; i >= 0; --i){
        delete shopItems.at(i);
    }
}

void Town::createDungeon(PerlinNoise*& myPerlin) {
    srand(time(0));
    int seed = rand();

    int MountainSeed = rand();

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {
            double perlinValue = myPerlin->OctavePerlin((i + seed) * (1.0 / size), (j + seed) * (1.0 / size), 1, 0.5, 15);

            if (perlinValue > 0.2) {
                townmapData[(i * size) + j] = 16;

                if (int(perlinValue * 1000) % 127 == 0) {
                    townmapData[(i * size) + j] = 19;
                    
                }
                else if (int(perlinValue * 1000) % 255 == 0) {
                    townmapData[(i * size) + j] = 20;
                    
                }

            }
            else {
                townmapData[(i * size) + j] = 0;
            }

        }
    }
}

void Town::CreateLocation(NameGenerator*& nameClass){
    srand(time(0));

    for(int i = 0; i < 5; ++i){
        
        int itemSeed = rand();
        int damage = 0, defense = 0, health = 0, mana = 0, range = 0, itemID = 0;

        stringstream name;
        vector<string>& adjectives = nameClass->getAdjectives();
        vector<string>& weapons = nameClass->getWeapons();
        vector<string>& sirnames = nameClass->getSirnames();

        name << adjectives.at(rand() % adjectives.size());
        

        itemID = itemSeed % 5;
        switch(itemID){
            case 0: //potion
                health = rand() % 20;
                name << " potion";
                break;
            case 1: //fighter
                damage = rand() % 256;
                name << " " << weapons.at(rand() % weapons.size());
                name << " of " << sirnames.at(rand() % sirnames.size());
                break;
            case 2: //mage
                name << " wand";
                name << " of " << sirnames.at(rand() % sirnames.size());
                mana = rand() % 25;
                range = rand() % 5;
                break;
            case 3: //tank
                damage = rand() % 256;
                name << " broadsword";
                name << " of " << sirnames.at(rand() % sirnames.size());
                break;
            case 4: //bard
                name << " flute";
                mana = rand() % 25;
                range = rand() % 5;
                break;
            default:
                break;
        }

        Item* newItem = new Item(itemID+1,damage,defense,health, mana, range, name.str() );

        shopItems.push_back(newItem);
    }
    //add variability in things like population, architecture.
    //Some little details to make it interesting
}

void Town::totalList(){
    cout << this->name << " is selling: \n";
    cout << "--------------------------------------\n";
    for(int i = 0; i < shopItems.size(); ++i){
        Item* listItem = shopItems.at(i);
        
        cout << (i+1) << ": " << listItem->getItemName();

        if(listItem->getItemID() % 2 != 0 && listItem->getItemID() != 1){
            cout << " : Manna : " << listItem->getManaRegen() << " : Range : " << listItem->getRange() << endl;
        }else if(listItem->getItemID() != 1){
            cout << " : Damage : " << listItem->getDamageRating() << endl;
        }else{
            cout << " : Health : " << listItem->getHealthRegen() << endl;
        }
    }
    cout << "--------------------------------------\n";
}