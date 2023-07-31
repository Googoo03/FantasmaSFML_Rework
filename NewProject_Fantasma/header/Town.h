#ifndef TOWN_H
#define TOWN_H

#include "../header/Location.h"
#include <vector>
#include "../header/Item.hpp"
#include "../header/NameGenerator.h"
#include "../header/PerlinNoise.h"

class Town : public Location {


    public:
        Town(int x, int y, int seed);
        ~Town();

        int* returnMapData() { return townmapData; }

        void createDungeon(PerlinNoise*&);
        void CreateLocation(NameGenerator*&);
        string getName(){return Location::name;}
        int getXPos(){return Location::xPos;}
        int getYPos(){return Location::yPos;}
        bool IsShopEmpty(){return (shopItems.size() == 0);}
        int getShopSize(){return shopItems.size();}
        void removeShopItem(int index){shopItems.erase(shopItems.begin()+index);}
        Item* getItem(int index){return shopItems.at(index);}

        void totalList();
    private:
        const static int size = 16;
        int townmapData[size*size];
        vector<Item*> shopItems;


};

#endif 