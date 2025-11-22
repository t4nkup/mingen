#include "mingen.h"

#ifndef _ENUM
#define _ENUM

// 
//  ENUM:  holds all of our enum declarations
//

typedef enum alphabet
{
    A = 0, B = 1000, C = 2000, D = 3000, E = 4000, F = 5000, G = 6000, H = 7000, I = 8000, J = 9000, K = 10000,
    L = 11000, M = 12000, N = 13000, O = 14000, P = 15000, Q = 16000, R = 17000, S = 18000, T = 19000, U = 20000,
    V = 21000, W = 22000, X = 23000, Y = 24000, Z = 25000,
}
alphabet;

typedef enum type
{
    // structs
    ARRAY =     A + 1,
    BUTTON =    B + 1,
    CHUNK =     C + 1,
    ENTRY =     E + 1,
    FLOAT3 =    F + 1,
    GAME =      G + 1,
    GRID =      G + 2,
    INT3 =      I + 1,
    MAP =       M + 1,
    MESH =      M + 2,
    SHAPE =     S + 1,
    TABLE =     T + 1,
    TRANSFORM = T + 2,
    UID =       U + 1,

    // shapes
    CUBE =      C + 100,
    RAMP =      R + 100,
}
type;

#endif