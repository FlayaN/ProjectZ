#ifndef SIMPLEXNOISE_H
#define SIMPLEXNOISE_H

#include <cstdint>
#include <cmath>

class Grad {
public:
	Grad( int8_t x, int8_t y) : x(x), y(y) {}
    int8_t x, y;
};
 
class SimplexNoise {
public:
    // Initialize permutation arrays
    static void init();
    // 2D simplex noise
    static double noise( double xin, double yin );
 
private:
    static int32_t fastFloor( double x );
    static double dot( const Grad& g, double x, double y );
    static const double F2;
    static const double G2;
	static const Grad grad2[12];
    static const Grad grad3[12];
    static const uint8_t p[256];
    static uint8_t perm[512];
    static uint8_t permMod12[512];
};

#endif