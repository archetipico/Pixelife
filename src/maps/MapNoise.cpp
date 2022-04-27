#include "MapNoise.hpp"

/* Construct noise, receives map */
MapNoise::MapNoise(Map *mapObject) {
    this->mapObject = mapObject;
    srand(time(0));
    seed = rand();
}

/* Construct noise, receives map and seed */
MapNoise::MapNoise(Map *mapObject, long seed) {
    this->mapObject = mapObject;
    this->seed = seed;
}

/* Destruct map in MapNoise */
MapNoise::~MapNoise() {
    delete mapObject;
    mapObject = nullptr;
}

/*
Thanks to https://www.redblobgames.com/maps/terrain-from-noise/

Generate noise:
- e is used for elevation based on SquareBump
- isGrass checks if the island has at least some grass,
    otherwise recreate it
- tree are placed as ones (1) into the heightmap
*/
void MapNoise::generate() {
    bool isGrass = false;
    bool isBorderWater = true;

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            float ny = 2.0f * y / h - 1;
            float nx = 2.0f * x / w - 1;
            float d = 1 - (1 - pow(ny, 2)) * (1 - pow(nx, 2));
            
            float e = 0.2 * getNoise(y, x, 5.0f) + 0.5 * getNoise(y, x, 2.0f);
            e /= (0.2 + 0.5);
            e += (1 - d) / 2;

            float val = pow(e, 4);
            if (val >= 0.09) {
                isGrass = true;
            }

            if ((y == 0 || y == h - 1 || x == 0 || x == w - 1) && val >= 0.06) {
                isBorderWater = false;
                break;
            }

            float tree = getNoise(y, x, 20.0f) + getNoise(y, x, 10.0f);
            if (tree > 0.50 && val >= 0.10 && val < 0.19) {
                val = 1;
            }


            mapObject->map[x][y] = val;
        }
    }

    if (!isGrass || !isBorderWater) {
        seed = rand();
        generate();
    }
}

/* Get noise, freq is the wave frequency */
float MapNoise::getNoise(int y, int x, float freq) {
    float ny = (float) y / h - 0.5f;
    float nx = (float) x / w - 0.5f;

    return noise2D(ny * freq, nx * freq);
}

/* Get permutation cell */
unsigned char MapNoise::noise(int x) {
    return (perm[x % 256] * seed) % 256;
}

/* Thanks to https://github.com/SRombauts/SimplexNoise/blob/master/src/SimplexNoise.cpp */
float MapNoise::noise2D(float x, float y) {
    float n0, n1, n2;   // Noise contributions from the three corners

    // Skewing/Unskewing factors for 2D
    static const float F2 = 0.366025403f;  // F2 = (sqrt(3) - 1) / 2
    static const float G2 = 0.211324865f;  // G2 = (3 - sqrt(3)) / 6   = F2 / (1 + 2 * K)

    // Skew the input space to determine which simplex cell we're in
    const float s = (x + y) * F2;  // Hairy factor for 2D
    const float xs = x + s;
    const float ys = y + s;
    const int i = floor(xs);
    const int j = floor(ys);

    // Unskew the cell origin back to (x,y) space
    const float t = static_cast<float>(i + j) * G2;
    const float X0 = i - t;
    const float Y0 = j - t;
    const float x0 = x - X0;  // The x,y distances from the cell origin
    const float y0 = y - Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int i1, j1;  // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0) {   // lower triangle, XY order: (0,0)->(1,0)->(1,1)
        i1 = 1;
        j1 = 0;
    } else {   // upper triangle, YX order: (0,0)->(0,1)->(1,1)
        i1 = 0;
        j1 = 1;
    }

    // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6

    const float x1 = x0 - i1 + G2;            // Offsets for middle corner in (x,y) unskewed coords
    const float y1 = y0 - j1 + G2;
    const float x2 = x0 - 1.0f + 2.0f * G2;   // Offsets for last corner in (x,y) unskewed coords
    const float y2 = y0 - 1.0f + 2.0f * G2;

    // Work out the hashed gradient indices of the three simplex corners
    const int gi0 = noise(i + noise(j));
    const int gi1 = noise(i + i1 + noise(j + j1));
    const int gi2 = noise(i + 1 + noise(j + 1));

    // Calculate the contribution from the first corner
    float t0 = 0.5f - x0*x0 - y0*y0;
    if (t0 < 0.0f) {
        n0 = 0.0f;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * smooth(gi0, x0, y0);
    }

    // Calculate the contribution from the second corner
    float t1 = 0.5f - x1*x1 - y1*y1;
    if (t1 < 0.0f) {
        n1 = 0.0f;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * smooth(gi1, x1, y1);
    }

    // Calculate the contribution from the third corner
    float t2 = 0.5f - x2*x2 - y2*y2;
    if (t2 < 0.0f) {
        n2 = 0.0f;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * smooth(gi2, x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 45.23065f * (n0 + n1 + n2)  / 1000;
}

/* Second derivative for smooth step */
float MapNoise::smooth(float x, float y, float s) {
    return (y-x) * ((s * (s * 6.0 - 15.0) + 10.0) * s * s * s) + x;
}