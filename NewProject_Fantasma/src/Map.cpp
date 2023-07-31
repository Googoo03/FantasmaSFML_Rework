#include "../header/Map.h"
#include "../header/PerlinNoise.h"
#include "../header/Dungeon.h"
#include "../header/NameGenerator.h"

Map::~Map(){

    for(int i = TownList.size()-1; i >= 0; --i){
        delete TownList.at(i);
    }
    for(int i = DungeonList.size()-1; i >= 0; --i){
        delete DungeonList.at(i);
    }
}



void Map::createMap(PerlinNoise*& myPerlin) {
    srand(time(0));
    int seed = rand();

    int MountainSeed = rand();

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {
            double perlinValue = myPerlin->OctavePerlin((i + seed) * (1.0 / size), (j + seed) * (1.0 / size), 3, 0.5, 5);
            double mountainValue = myPerlin->OctavePerlin((i + MountainSeed) * (1.0 / size), (j + MountainSeed) * (1.0 / size), 1, 0.5, 5);
            perlinValue += 2.0 / sqrt(pow(abs(center - i), 2) + pow(abs(center - j), 2));
            mountainValue += 2.0 / sqrt(pow(abs(center - i), 2) + pow(abs(center - j), 2));
            if (mountainValue > 0.4 && perlinValue > 0.5) {

                mapData[(i * size) + j] = 16; //SET BACK TO 17
            }
            else if (perlinValue > 0.2) {
                mapData[(i * size) + j] = 16;

                if (int(perlinValue * 1000) % 127 == 0) {
                    mapData[(i * size) + j] = 19;
                    TownList.push_back(new Town(i, j, seed));
                    //this is where we'll add T to the town list
                }
                else if (int(perlinValue * 1000) % 63 <= 10) {
                    mapData[(i * size) + j] = 20; 
                    Dungeon* newdungeon = new Dungeon(i, j, seed);
                    newdungeon->createDungeon(myPerlin);
                    DungeonList.push_back(newdungeon);
                }
                
            }
            else {
                mapData[(i * size) + j] = 0;
            }

        }
    }
}


void Map::marchingSquares(){
    mapData[(center * center) + center] = 20; //BossDungeonID

}

void Map::setDungeonIndex(int xQuad, int yQuad) {
    for (int i = 0; i < DungeonList.size(); ++i) {
        if (DungeonList.at(i)->getXPos() == yQuad && DungeonList.at(i)->getYPos() == xQuad) { //switch x and y quads???
            EnteredDungeon = true;
            DungeonIndex = i;
            break;
        }
    }
}


void Map::townEvent(NameGenerator*& nameClass){
    cout << "You have entered the Town \'" << returnTownName(TownList.at(TownIndex) ) << "\' \n\n" << endl;
    if(TownList.at(TownIndex)->IsShopEmpty()){
        TownList.at(TownIndex)->CreateLocation(nameClass);
    }
    TownList.at(TownIndex)->totalList();
}

void Map::dungeonEvent(){
    cout << "You have entered the Dungeon \'" << returnDungeonName(DungeonList.at(DungeonIndex) ) << "\' \n\n" << endl;
}

string Map::returnTownName(Town*& town){

    return town->getName();
}

string Map::returnDungeonName(Dungeon*& dungeon){

    return dungeon->getName();
}