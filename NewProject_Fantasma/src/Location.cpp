#include "../header/Location.h"
#include "time.h"
#include <cstdlib>

Location::Location(int x, int y, int seed): xPos(x), yPos(y){

    srand((x*y)+seed);
    int phonemeCount = nameLength;
    int phonemeIndex = ( (x*y)+seed) % 14;

    for(int i = 0; i < phonemeCount; ++i){ //Name generation using Phoneme list
 
        phonemeIndex = rand() % 14;
        name += phonemes[phonemeIndex];
    }
}