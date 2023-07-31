#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H


#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;

class PerlinNoise {

    public:
        int seed;
        
        //double getPositionValue() const;
        double perlinNoise(double x, double y);
        double grad(int hash, double x, double y);
        double lerp(double a, double b,double x);
        int increment(int x);
        double fade(double t);

        PerlinNoise(){
            srand(time(0));
            seed = 12;
        }
        double dotProduct(int x, int y);
        double OctavePerlin(double x, double y, int octaves, double persistence,double frequency);

        //PerlinNoise(int VecRes,int FinalRes, int seed);
    private:
        //const static int chunkSize = 20;
        //const static int VectorResolution = 10;
        //int FinalField[finalResolution]
        //int VectorField[VectorResolution][VectorResolution] = {};
        //int FinalField[chunkSize][chunkSize] = {};
        //double values[];
        

};

#endif