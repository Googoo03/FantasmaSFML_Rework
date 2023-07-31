#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

using namespace std;

class Location {

    public:
        string name;
        string phonemes[14] = {"s","t","p",
        "n","m","a",
        "e","i","o",
        "u","k","ch",
        "sh","l"}; //add more phonemes later

        Location(int x, int y, int seed);
        //virtual void CreateLocation() = 0;
    private:
        
        int nameLength = 20;
    protected:
        int xPos;
        int yPos;

};

#endif 