#include "../header/PerlinNoise.h"

static int RANDOMFIELD[256] = {114,52,69,183,141,89,178,162,112,133,214,26,77,72,224,55,88,142,98,240,44,109,94,194,30,118,22,150,110,132,242,107,99,209,250,61,181,123,199,16,197,170,62,137,58,128,145,87,54,19,182,103,130,190,91,203,212,241,217,180,237,189,81,7,78,251,223,84,201,232,14,100,74,144,167,119,249,158,231,230,244,111,243,57,45,115,172,198,161,126,131,42,166,80,134,90,253,50,233,31,63,192,67,6,156,220,179,12,28,160,76,23,108,85,206,73,228,138,236,8,153,38,34,202,196,39,48,226,174,247,185,17,120,255,176,117,49,210,1,122,218,106,124,175,147,35,25,200,59,252,18,92,66,47,60,154,152,3,159,246,27,136,102,245,21,0,125,184,171,157,13,82,116,51,188,143,163,177,36,216,235,221,208,148,64,5,222,97,186,139,146,33,9,254,229,113,155,93, 140, 149, 173, 104, 86, 127, 68, 234, 95, 151, 211, 53, 135, 165, 191, 24, 46, 207, 227, 2, 238, 187, 219, 96, 11, 65, 79, 248, 213, 195, 121, 41, 32, 215, 105, 20, 129, 239, 164,168, 10, 43, 56, 15, 40, 75, 37, 169, 70, 4, 205, 225, 29, 204, 101, 83, 71, 193};
  

double PerlinNoise::fade(double t){
    return t*t*t*(t*(t*6-15)+10);
}

double PerlinNoise::OctavePerlin(double x, double y, int octaves, double persistence, double frequency) {
		double total = 0;
		//double frequency = 1;
		double amplitude = 1;
		double maxValue = 0;			// Used for normalizing result to 0.0 - 1.0
		for(int i=0;i<octaves;i++) {
			total += perlinNoise(x * frequency, y * frequency) * amplitude;
			
			maxValue += amplitude;
			
			amplitude *= persistence;
			frequency *= 2;
		}
		
		return total/maxValue;
	}

int PerlinNoise::increment(int x){

    return (x+1)>255 ? (x+1)%255 : (x+1);
}

double PerlinNoise::lerp(double a, double b,double x){

    return a+(x*(b-a));
}

double PerlinNoise::grad(int hash, double x, double y){
    //cout << (hash & 5) << endl;
    switch(hash & 0x5){

        case 0x0: return  x + y;
        case 0x1: return -x + y;
        case 0x2: return  x - y;
        case 0x3: return -x - y;
        case 0x4: return  y + x;
        case 0x5: return  y - x;
        default: return 0;
    }
}

double PerlinNoise::perlinNoise(double x, double y){
    int xinteger = (int)(x) % 255;
    int yinteger = (int)(y) % 255;
    double xfloat = (x) - (int)(x);
    double yfloat = (y) - (int)(y);
    //cout << xinteger <<" "<<yinteger<<" "<<xfloat<<" "<<yfloat<<endl;
    double u = fade(xfloat);
    double v = fade(yfloat);

    int aa,ab,ba,bb;
    aa=RANDOMFIELD[(RANDOMFIELD[xinteger]+yinteger) % 256];
    ab=RANDOMFIELD[(RANDOMFIELD[xinteger]+increment(yinteger)) % 256];
    ba=RANDOMFIELD[(RANDOMFIELD[increment(xinteger)]+yinteger) % 256];
    bb=RANDOMFIELD[(RANDOMFIELD[increment(xinteger)]+increment(yinteger)) % 256];
    //cout << aa << " " << ab << " " << ba << " " << bb << endl;
    double x1 = lerp( grad(aa,xfloat,yfloat),grad(ab,xfloat-1,yfloat),u);
    //cout << "Gradfunc: " << grad(aa,xfloat,yfloat) << endl << grad(aa,xfloat-1,yfloat) << endl << u<<endl;

    double x2 = lerp(grad(ba,xfloat,yfloat-1),grad(bb,xfloat-1,yfloat-1),u);
    //cout << "x1: " << x1 <<" x2: " << x2 << endl;

    return lerp(x1,x2,v);
}

