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

int Map::getTileValue(int tile) {
    return mapData[tile];
}


void Map::createMap() {

    PerlinNoise* myPerlin = new PerlinNoise();

    srand(time(0));
    int seed = rand();

    int MountainSeed = rand();

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {

            int tile = (i * size) + j;

            double perlinValue = myPerlin->OctavePerlin((i + seed) * (1.0 / size), (j + seed) * (1.0 / size), 3, 0.5, 5);
            double mountainValue = myPerlin->OctavePerlin((i + MountainSeed) * (1.0 / size), (j + MountainSeed) * (1.0 / size), 1, 0.5, 5);
            perlinValue += 2.0 / sqrt(pow(abs(center - i), 2) + pow(abs(center - j), 2));
            mountainValue += 2.0 / sqrt(pow(abs(center - i), 2) + pow(abs(center - j), 2));
            if (mountainValue > 0.4 && perlinValue > 0.5) {

                mapData[tile] = 17; //SET BACK TO 17
            }
            else if (perlinValue > 0.2) {
                mapData[tile] = 16;

                if (int(perlinValue * 1000) % 127 == 0) {
                    mapData[tile] = 19;
                    TownList.push_back(new Town(i, j, seed));
                    //this is where we'll add T to the town list
                }
                else if (int(perlinValue * 1000) % 63 <= 2) {
                    mapData[tile] = 20;
                    Dungeon* newdungeon = new Dungeon(i, j, seed);
                    newdungeon->createDungeon(myPerlin);
                    DungeonList.push_back(newdungeon);
                }
                
            }
            else {
                mapData[tile] = 0;
            }

        }
    }
    marchingSquares();
    loadTilemap(mapData, 0);


    delete myPerlin;
}


void Map::loadTilemap(int* tileData, int scene) {
    if (!mapTiles.load("Tilemap.png", sf::Vector2u(8, 8), size, tileData, scene))  return;
    mapTiles.setScale(8, 8);
}


void Map::marchingSquares(){
    mapData[(center*center)+center] = 20; //BossDungeonID

}

void Map::enterStructure(int playerTile) {
    int dungeonTile;
    for (int i = 0; i < DungeonList.size(); ++i) {
        dungeonTile = (DungeonList.at(i)->getXPos() * size) + DungeonList.at(i)->getYPos();
        if (dungeonTile == playerTile) { //switch x and y quads???
            EnteredDungeon = true;
            DungeonIndex = i;
            cout << "You entered dungeon " << endl;
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