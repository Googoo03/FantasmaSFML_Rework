#ifndef DUNGEON_H
#define DUNGEON_H

#include "../header/Location.h"
#include <vector>
#include "../header/Item.hpp"
#include "../header/NameGenerator.h"
#include "../header/PerlinNoise.h"
#include "../header/Bandit.hpp"

class Dungeon : public Location {


    public:
        Dungeon(int x, int y, int seed);
        void CreateLocation(NameGenerator*);
        string getName(){return Location::name;}

        int* returnMapData() { return dungeonmapData; }
        vector<Bandit*>& returnEnemies() { return enemies; }

        int getXPos(){return Location::xPos;}
        int getYPos(){return Location::yPos;}

        void createDungeon(PerlinNoise*& myPerlin);
        
    private:
        vector<Bandit*> enemies;
        const static int size = 16;
        int center = size / 2;
        int dungeonmapData[size * size];


};

#endif 