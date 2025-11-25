#include "mingen.h"

#ifndef _ENUM
#define _ENUM

// forward declare values
typedef uint8_t uid[16];
typedef int int3[3];
typedef float float3[3];

// forward declare types
typedef struct array array;
typedef struct button button;
typedef struct chunk chunk;
typedef struct entry entry;
typedef struct FN FN;
typedef struct game game;
typedef struct grid grid;
typedef struct list list;
typedef struct map map;
typedef struct mesh mesh;
typedef struct shape shape;
typedef struct table table;
typedef struct transform transform;

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
    CHUNK =     C + 100,
    ENTRY =     E + 100,
    GAME =      G + 100,
    GRID =      G + 101,
    LIST =      L + 100,
    MAP =       M + 100,
    MESH =      M + 101,
    SHAPE =     S + 100,
    TABLE =     T + 100,
    TRANSFORM = T + 101,

    // shape
    CUBE =      C + 200,
    RAMP =      R + 200,
}
type;

#endif