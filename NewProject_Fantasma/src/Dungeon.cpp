#include "../header/Dungeon.h"

#include <cstdlib>

using namespace std;

Dungeon::Dungeon(int x, int y, int seed) : Location{x,y,seed} {
}

void Dungeon::createDungeon(PerlinNoise*& myPerlin) {
    srand(time(0));
    int seed = rand();

    int MountainSeed = rand();

    int enemyPos = seed % (size * size);

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {
            double perlinValue = myPerlin->OctavePerlin((i + seed) * (1.0 / size), (j + seed) * (1.0 / size), 1, 0.5, 2);
            perlinValue += 2.0 / sqrt(pow(abs(center - i), 2) + pow(abs(center - j), 2));
            

            if (j == size / 2) {
                if (i == size - 1) {
                    dungeonmapData[(i * size) + j] = 21;
                }
                else {
                    dungeonmapData[(i * size) + j] = 16;
                }
                continue;
            }

            if (perlinValue > 0.2 && perlinValue < 0.6) {
                dungeonmapData[(i * size) + j] = 16;

                if (int(perlinValue * 1000) % 127 == 0) {
                    dungeonmapData[(i * size) + j] = 19;
                    enemies.push_back(new Bandit(10, 10, 208, 0, sf::Vector2u(64 * j, 64 * i)));

                }
                else if (int(perlinValue * 1000) % 255 == 0) {
                    dungeonmapData[(i * size) + j] = 18;

                }

            }
            else {
                dungeonmapData[(i * size) + j] = 0;
            }
            if (dungeonmapData[(i * size) + j] == 16) { //if current tile is ground and enemy spawn, then spawn enemy

                
            }
            
            }
        }
    }

void Dungeon::CreateLocation(NameGenerator* name){

    //add implementation
}