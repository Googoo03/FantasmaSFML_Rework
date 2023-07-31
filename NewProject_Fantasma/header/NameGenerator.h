#ifndef NAMEGEN_H
#define NAMEGEN_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class NameGenerator {
    public:
        NameGenerator();
        vector<string>& getAdjectives(){return adjectives;}
        vector<string>& getWeapons(){return weapons;}
        vector<string>& getSirnames(){return sirnames;}
    private:
        vector<string> adjectives ={"scrawny",
"rainy",
"kindhearted",
"hallowed",
"educated",
"bloody",
"weary",
"unbiased",
"stunning",
"near",
"dashing",
"burly",
"tacky",
"quick",
"onerous",
"miscreant",
"keen",
"jittery",
"whimsical",
"nimble"};
        vector<string> weapons ={"longsword", "bowstaff", "dagger", "stick"};
        vector<string> sirnames = {"Draxus", "Onesirus", "Cthulu", "Pharonius"};
};


#endif