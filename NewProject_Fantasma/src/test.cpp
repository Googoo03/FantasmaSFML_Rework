#include "../header/PerlinNoise.h"
#include "../header/Map.h"
#include <iostream>

using namespace std;

int main(){
    PerlinNoise* myPerlin = new PerlinNoise(); //This needs a destructor!!!

    Map newMap;
    
    newMap.createMap(myPerlin);
    newMap.marchingSquares();
    

    while(true){
        newMap.drawMap();
        cout << "Waiting for keypress... " << endl;
        char input = getchar();
        newMap.movementValidation(input);
        
        if(input == '-') return 0;
    }
    return 0;
}