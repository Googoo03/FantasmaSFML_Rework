#ifndef MAP_H
#define MAP_H

#include "../header/PerlinNoise.h"
#include "../header/Town.h"
#include "../header/Dungeon.h"
#include "../header/Location.h"
#include "../header/NameGenerator.h"

#include "../header/Tilemap.h"
#include <cstdlib>

class Map {

    public:
        int center;
        const static int size = 16;
        int mapData[size*size];

        //inlcude another list for dungeons

        Map():center(size/2), playerX(center),playerY(center){}
        ~Map();
        void createMap();
       

        void townEvent(NameGenerator*&);
        void dungeonEvent();

        void marchingSquares();
        void movementValidation(char input);
        bool getEnteredTown(){return EnteredTown;}

        bool getEnteredDungeon(){return EnteredDungeon;}
        bool getExit() { return Exit; }
        bool getEnteredBoss(){return EnteredBoss;}

        void flipEnteredDungeon() { EnteredDungeon = !EnteredDungeon; }
        void flipExit() { Exit = !Exit; }

        string returnTownName(Town*& town);
        string returnDungeonName(Dungeon*& dungeon);
        int* returnMapData() { return mapData; }

        Town* returnTown(){ return TownList.at(TownIndex);}
        Dungeon* returnDungeon() { return DungeonList.at(DungeonIndex); }

        void setDungeonIndex(int, int);


        void loadTilemap(int*, int);
        Tilemap returnTilemap() { return mapTiles; }
    private:
        Tilemap mapTiles;
        

        vector<Town*>  TownList;
        vector<Dungeon*>  DungeonList;
        int playerX,playerY;

        bool EnteredTown;
        bool EnteredDungeon;
        bool Exit;
        bool EnteredBoss;

        int DungeonIndex;
        int TownIndex;
};

#endif