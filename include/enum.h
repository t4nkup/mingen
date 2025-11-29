#include "mingen.h"

#ifndef ENUM
#define ENUM

typedef enum alphabet
{
    A = 0, 
    B = 1000, 
    C = 2000, 
    D = 3000, 
    E = 4000, 
    F = 5000, 
    G = 6000, 
    H = 7000, 
    I = 8000, 
    J = 9000, 
    K = 10000,
    L = 11000, 
    M = 12000, 
    N = 13000, 
    O = 14000, 
    P = 15000, 
    Q = 16000, 
    R = 17000, 
    S = 18000, 
    T = 19000, 
    U = 20000,
    V = 21000, 
    W = 22000, 
    X = 23000, 
    Y = 24000, 
    Z = 25000,
}
alphabet;

typedef enum type
{
    // value
    BOOL =      B + 1,
    FLOAT =     F + 1,
    FLOAT3 =    F + 2,
    INT =       I + 1,
    INT3 =      I + 2,
    STRING =    S + 1,
    UID =       U + 1,

    // struct
    ARRAY =     A + 100,
    BUTTON =    B + 100,
    CAMERA =    C + 101,
    CHUNK =     C + 100,
    ENTRY =     E + 100,
    GAME =      G + 101,
    GRID =      G + 100,
    LIST =      L + 100,
    MAP =       M + 101,
    MESH =      M + 100,
    SHAPE =     S + 100,
    TABLE =     T + 100,
    TRANSFORM = T + 101,

    // shape
    CUBE =      C + 200,
    RAMP =      R + 200,
}
type;

#endif